#include "PostProcessFramebuffer.h"

PostProcessFramebuffer::PostProcessFramebuffer(unsigned int width, unsigned int height, GLenum filter, Attachment::Type type)
{
	FBO::init(width, height);
	this->textures[BUFFER0] = Attachment::get(type, width, height, filter, filter);
	this->textures[BUFFER1] = Attachment::get(type, width, height, filter, filter);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + BUFFER0, GL_TEXTURE_2D, this->textures[BUFFER0], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1 + BUFFER1, GL_TEXTURE_2D, this->textures[BUFFER1], 0);
	this->check(LENGTH);
}

void PostProcessFramebuffer::destroy()
{
	if (glIsTexture(this->textures[BUFFER0]) == GL_TRUE) glDeleteTextures(1, &this->textures[BUFFER0]);
	if (glIsTexture(this->textures[BUFFER1]) == GL_TRUE) glDeleteTextures(1, &this->textures[BUFFER1]);
	FBO::destroy();
}
