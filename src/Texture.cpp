//
//  Texture.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Texture.h"

TextureLoader::TextureLoader(const char* path)
{
    FILE* file = File::open(path, "rb");
    if(!file) {
        printf("Error: Could not open/find texture [%s].", path);
        throw -1;
    }

    GLubyte header[12];
    if(fread(&header, sizeof(header), 1, file) == 0) {
        printf("Error: Could not read texture [%s].", path);
        throw -1;
    }

    const static GLubyte TGA_COMPRESSED_HEADER[] = {0,0,10,0,0,0,0,0,0,0,0,0};
    if(memcmp(header, TGA_COMPRESSED_HEADER, sizeof(header)) != 0) {
        printf("Error: Header of texture [%s] invalid.", path);
        throw -1;
    }

    GLubyte description[6];
    if(fread(description, sizeof(description), 1, file) == 0) {
        printf("Error reading texture [%s].", path);
        throw -1;
    }

    this->width = description[1] * 256 + description[0];
    this->height = description[3] * 256 + description[2];
    GLuint bitsPerPixel = description[4];

    if(width <= 0 || height <= 0 || (bitsPerPixel != 24 && bitsPerPixel != 32)) {
        printf("Error: Invalid tga texture [%s]. W[%i] H[%i] B[%i].", path, this->width, this->height, bitsPerPixel);
        throw -1;
    }

    this->type = GL_RGB;
    if(bitsPerPixel == 32)
        this->type = GL_RGBA;

    GLuint bytesPerPixel = bitsPerPixel / 8;
    GLuint pixelCount = this->width * this->height;
    this->imageSize = bytesPerPixel * this->width * this->height;

    this->data = (GLubyte*) malloc(imageSize);
    if(!this->data) {
        printf("Memory allocation error!");
        throw -1;
    }

    GLuint currentPixel = 0;
    GLuint currentByte = 0;
    GLubyte* colorBuffer = (GLubyte*) malloc(bytesPerPixel);

    do
    {
        GLubyte chunkHeader = 0;
        if(fread(&chunkHeader, sizeof(GLubyte), 1, file) == 0) {
            printf("Error reading TGA [%s] color data chunk header.", path);
            throw -1;
        }

        if(chunkHeader < 128)
        {
            chunkHeader ++;
            for(short counter = 0; counter < chunkHeader; counter ++) {
                if(fread(colorBuffer, 1, bytesPerPixel, file) != bytesPerPixel) {
                    printf("Error reading TGA [%s] color data.", path);
                    throw -1;
                }

                this->data[currentByte] = colorBuffer[2];
                this->data[currentByte + 1] = colorBuffer[1];
                this->data[currentByte + 2] = colorBuffer[0];
                if(bytesPerPixel == 4)
                    this->data[currentByte + 3] = colorBuffer[3];
                currentByte += bytesPerPixel;
                currentPixel ++;
            }
        }
        else
        {
            chunkHeader -= 127;
            if(fread(colorBuffer, 1, bytesPerPixel, file) != bytesPerPixel) {
                printf("Error reading TGA [%s] color data.", path);
                throw -1;
            }

            for(short counter = 0; counter < chunkHeader; counter ++) {
                data[currentByte] = colorBuffer[2];
                data[currentByte + 1] = colorBuffer[1];
                data[currentByte + 2] = colorBuffer[0];
                if(bytesPerPixel == 4)
                    data[currentByte + 3] = colorBuffer[3];
                currentByte += bytesPerPixel;
                currentPixel ++;
            }
        }
    }
    while(currentPixel < pixelCount);

    fclose(file);
    free(colorBuffer);
}

TextureLoader::~TextureLoader()
{
    if(this->data != NULL) free(this->data);
}

void Texture::load(const char* path)
{
    TextureLoader loader = TextureLoader(path);
    this->dimensions = glm::uvec2(loader.width, loader.height);
    
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, loader.type, loader.width, loader.height, 0, loader.type, GL_UNSIGNED_BYTE, loader.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::destroy() {
    if(glIsTexture(id) == GL_TRUE)
        glDeleteTextures(1, &id);
}
