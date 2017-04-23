//
//  Texture.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GL.h"
#include "File.h"

class TextureLoader
{
public:
    unsigned int width, height;
    unsigned long imageSize;
    GLenum type;
    GLubyte* data;

    TextureLoader(const char* path);
    ~TextureLoader();
};

class Texture
{
    GLenum id;

public:
    Texture() {}
    void load(const char* path);
    void destroy();

    void bind(GLenum uniform, int target) const {
        glActiveTexture(GL_TEXTURE0 + target);
        glBindTexture(GL_TEXTURE_2D, this->id);
        glUniform1i(uniform, target);
    }
};

#endif /* Texture_hpp */
