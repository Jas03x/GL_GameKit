#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "GL.h"

namespace Attachment
{
	typedef enum
	{
		NONE,
		RGB_8UI,
		RGB_16F,
		RGB_32F,
		RGBA_8UI,
		RGBA_16F,
		RGBA_32F,
		DEPTH_16F,
		DEPTH_32F,
        DEPTH_STENCIL,
		LENGTH
	}Type;

	// table format:
	// [internal format] [format] [type]
	extern const GLenum TABLE[LENGTH][3];

	GLuint get(Type id, unsigned int width, unsigned int height, GLenum mag_filter = GL_NEAREST, GLenum min_filter = GL_NEAREST);
}

#endif
