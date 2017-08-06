//
//  DSFramebuffer.h
//  Automata
//
//  Created by Jas S on 2017-08-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DSFramebuffer_h
#define DSFramebuffer_h

#include <stdio.h>

#include "Framebuffer.h"

class DSFramebuffer : public FBO // deferred shading framebuffer
{
public:
    enum TextureID
    {
        DIFFUSE_TEXTURE = 0,
        NORMAL_TEXTURE = 1,
        SPECULAR_TEXTURE = 2,
        LIGHT_TEXTURE = 3,
        DEPTH_TEXTURE = 4,
        LENGTH = 5
    };
    
private:
    GLuint textures[LENGTH];
    
public:
    DSFramebuffer(){}
    DSFramebuffer(unsigned int width, unsigned int height, GLenum filter = GL_NEAREST, Attachment::Type texture_type = Attachment::RGB_16F, Attachment::Type normal_type = Attachment::RGB_16F, Attachment::Type depth_type = Attachment::DEPTH_STENCIL);
    
    void initalize(unsigned int width, unsigned int height, GLenum filter, Attachment::Type texture_type, Attachment::Type normal_type, Attachment::Type depth_type);
    void destroy();
    
    inline GLuint getDiffuseTexture()  const { return this->textures[DIFFUSE_TEXTURE]; }
    inline GLuint getNormalTexture()   const { return this->textures[NORMAL_TEXTURE]; }
    inline GLuint getLightTexture()    const { return this->textures[LIGHT_TEXTURE]; }
    inline GLuint getSpecularTexture() const { return this->textures[SPECULAR_TEXTURE]; }
    inline GLuint getDepthTexture()    const { return this->textures[DEPTH_TEXTURE]; }
    
    inline void bindGeometryBuffers() const {
        static const GLenum GEOMETRY_BUFFERS[3] = { GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE, GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE, GL_COLOR_ATTACHMENT0 + SPECULAR_TEXTURE };
        glDrawBuffers(3, GEOMETRY_BUFFERS);
    }
    
    inline void bindLightingBuffers() const {
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + LIGHT_TEXTURE);
    }
    
    void bindTexture(GLenum uniform, TextureID index, int target) const {
        glActiveTexture(GL_TEXTURE0 + target);
        glBindTexture(GL_TEXTURE_2D, this->textures[index]);
        glUniform1i(uniform, target);
    }
};

#endif /* DSFramebuffer_h */
