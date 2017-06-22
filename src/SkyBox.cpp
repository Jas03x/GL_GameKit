#include "SkyBox.h"

SkyBox::SkyBox(const char* tex_path)
{
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    TextureLoader loader = TextureLoader(tex_path);
    for(unsigned int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, loader.type, loader.width, loader.height, 0, loader.type, GL_UNSIGNED_BYTE, loader.data);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}

SkyBox::SkyBox(const std::array<std::string, 6>& tex_paths)
{
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    for(unsigned int i = 0; i < 6; i++)
    {
        TextureLoader loader = TextureLoader(tex_paths[i].c_str());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, loader.type, loader.width, loader.height, 0, loader.type, GL_UNSIGNED_BYTE, loader.data);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}

void SkyBox::destroy()
{
    if(glIsTexture(this->texture) == GL_TRUE) glDeleteTextures(1, &this->texture);
}
