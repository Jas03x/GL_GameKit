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
#include "Attachment.h"

class FBO // general purpose framebuffer
{
protected:
    GLuint id;
    glm::uvec2 dimensions;
    
	void init(unsigned int width, unsigned int height);
	void check(unsigned int attachments);
	void destroy();

public:
    FBO(){}
    
    inline void bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, this->id);
        glViewport(0, 0, this->dimensions.x, this->dimensions.y);
    }
    
    inline void unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, this->dimensions.x, this->dimensions.y);
    }
    
    inline const glm::uvec2& getDimensions() const { return this->dimensions; }
};

class Framebuffer : public FBO // regular framebuffer
{
private:
	GLuint texture_attachment;
	GLuint depth_attachment;

public:
	Framebuffer() {}
	void init(unsigned int width, unsigned int height, Attachment::Type texture_type, Attachment::Type depth_type);
	void destroy();
};

class DSFramebuffer : public FBO // deferred shading framebuffer
{
public:
	enum TextureID
	{
		DIFFUSE_TEXTURE = 0,
		NORMAL_TEXTURE = 1,
		LIGHT_TEXTURE = 2,
		DEPTH_TEXTURE = 3,
		LENGTH = 4
	};

private:
	// 0 - diffuse
	// 1 - normal
	// 2 - depth
	GLuint textures[LENGTH];

public:
	DSFramebuffer() {}
	void init(unsigned int width, unsigned int height, GLenum filter = GL_NEAREST, Attachment::Type texture_type = Attachment::RGB_16F, Attachment::Type normal_type = Attachment::RGB_16F, Attachment::Type depth_type = Attachment::DEPTH_STENCIL);
	void destroy();

	inline GLuint getDiffuseTexture() const { return this->textures[DIFFUSE_TEXTURE]; }
	inline GLuint getNormalTexture()  const { return this->textures[NORMAL_TEXTURE]; }
	inline GLuint getLightTexture()   const { return this->textures[LIGHT_TEXTURE]; }
	inline GLuint getDepthTexture()   const { return this->textures[DEPTH_TEXTURE]; }

	inline void bindGeometryBuffers() const { 
		static const GLenum GEOMETRY_BUFFERS[3] = { GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE, GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE, GL_COLOR_ATTACHMENT0 + LIGHT_TEXTURE };
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

#endif /* Framebuffer_hpp */
