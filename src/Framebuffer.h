//
//  Framebuffer.hpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp

#include <stdio.h>

#include "GL.h"
#include "GLM.h"

class Framebuffer
{
private:
    GLuint id;
    GLuint texture;
    GLuint depth_buffer;
    glm::uvec2 dimensions;
    
public:
    Framebuffer(){}
    void init(unsigned int width, unsigned int height);
    void destroy();
    
    inline void bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, this->id);
        glViewport(0, 0, this->dimensions.x, this->dimensions.y);
    }
    
    inline void unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, this->dimensions.x, this->dimensions.y);
    }
    
    inline GLuint getTexture() const { return this->texture; }
};

#endif /* Framebuffer_hpp */
