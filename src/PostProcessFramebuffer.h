#ifndef POST_PROCESS_FRAMEBUFFER_H
#define POST_PROCESS_FRAMEBUFFER_H

#include "Framebuffer.h"

/*
 * Post processing framebuffer (for gaussion blurs and such)
 * NOTE: DOES NOT HAVE A DEPTH ATTACHMENT! DO NOT FORGET TO DISABLE DEPTH TESTING BEFORE USING
*/

class PostProcessFramebuffer : public FBO
{
public:
	enum TextureID
	{
		BUFFER0,
		BUFFER1,
		LENGTH
	};

	PostProcessFramebuffer() {}
	PostProcessFramebuffer(unsigned int width, unsigned int height, GLenum filter = GL_NEAREST, Attachment::Type type = Attachment::Type::RGBA_16F);
	void destroy();

	inline GLuint getBuffer0() const { return this->textures[BUFFER0]; }
	inline GLuint getBuffer1() const { return this->textures[BUFFER1]; }
	inline void bindBuffer0() const { glDrawBuffer(GL_COLOR_ATTACHMENT0 + BUFFER0); }
	inline void bindBuffer1() const { glDrawBuffer(GL_COLOR_ATTACHMENT1 + BUFFER1); }
	inline void bindColorBuffers() const {
		static const GLenum COLOR_BUFFERS[2] = {GL_COLOR_ATTACHMENT0 + BUFFER0, GL_COLOR_ATTACHMENT1 + BUFFER1};
		glDrawBuffers(2, COLOR_BUFFERS);
	}

private:
	GLuint textures[LENGTH];
};

#endif /* POST_PROCESS_FRAMEBUFFER_H */