#ifndef POINT_LIGHT_RENDERER_H
#define POINT_LIGHT_RENDERER_H

#include "GL.h"
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Framebuffer.h"

class PointLightRenderer : public Shader
{
private:
	const DSFramebuffer* framebuffer;
	GLuint mvp_matrix;
	GLuint inv_proj_matrix; // inverse projection matrix
	GLuint light_position; // light position in eye space
	GLuint light_color;
	GLuint diffuse_texture;
	GLuint normal_texture;
	GLuint depth_texture;
	GLuint screen_size;

	glm::vec2 screen_dimensions;

public:
	PointLightRenderer() {}
	void load(unsigned int width, unsigned int height, const DSFramebuffer& fbo);
	void render(const Light::PointLight& light);
	void destroy();
};

#endif