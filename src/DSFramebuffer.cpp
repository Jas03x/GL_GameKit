//
//  DSFramebuffer.cpp
//  Automata
//
//  Created by Jas S on 2017-08-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DSFramebuffer.h"

DSFramebuffer::DSFramebuffer(unsigned int width, unsigned int height, GLenum filter, Attachment::Type diffuse_type, Attachment::Type normal_type, Attachment::Type depth_type)
{
    FBO::init(width, height);
    this->textures[DIFFUSE_TEXTURE] = Attachment::get(diffuse_type, width, height, filter, filter);
    this->textures[NORMAL_TEXTURE] = Attachment::get(normal_type, width, height, filter, filter);
	this->textures[BRIGHTNESS_TEXTURE] = Attachment::get(Attachment::R_8F, width, height, filter, filter);
    this->textures[LIGHT_TEXTURE] = Attachment::get(diffuse_type, width, height, filter, filter);
    this->textures[SPECULAR_TEXTURE] = Attachment::get(diffuse_type, width, height, filter, filter);
    this->textures[DEPTH_TEXTURE] = Attachment::get(depth_type, width, height, filter, filter);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE, GL_TEXTURE_2D, this->textures[DIFFUSE_TEXTURE], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE,  GL_TEXTURE_2D, this->textures[NORMAL_TEXTURE],  0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + BRIGHTNESS_TEXTURE, GL_TEXTURE_2D, this->textures[BRIGHTNESS_TEXTURE], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + LIGHT_TEXTURE,   GL_TEXTURE_2D, this->textures[LIGHT_TEXTURE],   0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + SPECULAR_TEXTURE, GL_TEXTURE_2D, this->textures[SPECULAR_TEXTURE], 0);
    if(depth_type != Attachment::DEPTH_STENCIL)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->textures[DEPTH_TEXTURE], 0);
    else
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->textures[DEPTH_TEXTURE], 0);
    this->check(LENGTH - 1);
}

void DSFramebuffer::destroy()
{
    if (glIsTexture(this->textures[DIFFUSE_TEXTURE]) == GL_TRUE) glDeleteTextures(1, &this->textures[DIFFUSE_TEXTURE]);
    if (glIsTexture(this->textures[NORMAL_TEXTURE]) == GL_TRUE)  glDeleteTextures(1, &this->textures[NORMAL_TEXTURE]);
	if (glIsTexture(this->textures[BRIGHTNESS_TEXTURE] == GL_TRUE)) glDeleteTextures(1, &this->textures[BRIGHTNESS_TEXTURE]);
    if (glIsTexture(this->textures[LIGHT_TEXTURE]) == GL_TRUE)   glDeleteTextures(1, &this->textures[LIGHT_TEXTURE]);
    if (glIsTexture(this->textures[SPECULAR_TEXTURE] == GL_TRUE)) glDeleteTextures(1, &this->textures[SPECULAR_TEXTURE]);
    if (glIsTexture(this->textures[DEPTH_TEXTURE]) == GL_TRUE)   glDeleteTextures(1, &this->textures[DEPTH_TEXTURE]);
    FBO::destroy();
}
