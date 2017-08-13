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

/*
 * Deferred shading framebuffer
 *
 * We could do swap this class into 2 different framebuffers but it might be expensive to
 * switch buffers unneccessarily, so we use this multi-purpose buffer
 *
 */

class DSFramebuffer : public FBO
{
public:
    enum TextureID
    {
        DIFFUSE_TEXTURE = 0,
        NORMAL_TEXTURE = 1,
		BRIGHTNESS_TEXTURE = 2,
        LIGHT_TEXTURE = 3,
		SPECULAR_TEXTURE = 4,
        DEPTH_TEXTURE = 5,
        LENGTH = 6
    };
   
    DSFramebuffer(){}
	DSFramebuffer(unsigned int width, unsigned int height, GLenum filter = GL_NEAREST, Attachment::Type diffuse_type = Attachment::RGB_16F, Attachment::Type normal_type = Attachment::RGB_16F, Attachment::Type depth_type = Attachment::DEPTH_STENCIL);
    void destroy();
    
    inline GLuint getDiffuseTexture()  const { return this->textures[DIFFUSE_TEXTURE]; }
    inline GLuint getNormalTexture()   const { return this->textures[NORMAL_TEXTURE]; }
	inline GLuint getBrightnessTexture() const { return this->textures[BRIGHTNESS_TEXTURE]; }
    inline GLuint getLightTexture()    const { return this->textures[LIGHT_TEXTURE]; }
    inline GLuint getSpecularTexture() const { return this->textures[SPECULAR_TEXTURE]; }
    inline GLuint getDepthTexture()    const { return this->textures[DEPTH_TEXTURE]; }
    
	inline void bindColorBuffers() const {
		static const GLenum ALL_BUFFERS[5] = {
			GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE,
			GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE,
			GL_COLOR_ATTACHMENT0 + BRIGHTNESS_TEXTURE,
			GL_COLOR_ATTACHMENT0 + LIGHT_TEXTURE,
			GL_COLOR_ATTACHMENT0 + SPECULAR_TEXTURE
		};
		glDrawBuffers(5, ALL_BUFFERS);
	}

    inline void bindGeometryBuffers() const {
        static const GLenum GEOMETRY_BUFFERS[3] = { GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE, GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE, GL_COLOR_ATTACHMENT0 + BRIGHTNESS_TEXTURE };
        glDrawBuffers(3, GEOMETRY_BUFFERS);
    }
    
    inline void bindLightingBuffers() const {
		static const GLenum LIGHTING_BUFFERS[2] = { GL_COLOR_ATTACHMENT0 + LIGHT_TEXTURE, GL_COLOR_ATTACHMENT0 + SPECULAR_TEXTURE };
        glDrawBuffers(2, LIGHTING_BUFFERS);
    }
    
    void bindTexture(GLenum uniform, TextureID index, int target) const {
        glActiveTexture(GL_TEXTURE0 + target);
        glBindTexture(GL_TEXTURE_2D, this->textures[index]);
        glUniform1i(uniform, target);
    }

private:
	GLuint textures[LENGTH];
};

#endif /* DSFramebuffer_h */
