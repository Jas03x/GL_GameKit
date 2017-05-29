#include "Attachment.h"

const GLenum Attachment::TABLE[Attachment::LENGTH][3] =
{
    {GL_NONE, GL_NONE, GL_NONE},
    // RGB
    {GL_RGB, GL_RGB, GL_UNSIGNED_BYTE}, // RGB_8UI
    {GL_RGB16F, GL_RGB, GL_FLOAT}, // RGB_16F
    {GL_RGB32F, GL_RGB, GL_FLOAT}, // RGB_32F
    // RGBA
    { GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE}, // RGBA_8UI
    { GL_RGBA16F, GL_RGB, GL_FLOAT }, // RGBA_16F
    { GL_RGBA32F, GL_RGB, GL_FLOAT }, // RGBA_32F,
    // DEPTH
    {GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_FLOAT}, // DEPTH_16F
    {GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT},  // DEPTH_32F
    {GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8} // DEPTH_STENCIL
};

GLuint Attachment::get(Type id, unsigned int width, unsigned int height, GLenum mag_filter, GLenum min_filter)
{
	if (id == NONE) return 0;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, TABLE[id][0], width, height, 0, TABLE[id][1], TABLE[id][2], 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return texture;
}
