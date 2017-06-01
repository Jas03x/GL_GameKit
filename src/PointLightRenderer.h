#ifndef POINT_LIGHT_RENDERER_H
#define POINT_LIGHT_RENDERER_H

#include "GL.h"
#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "PointLight.h"
#include "Framebuffer.h"

class PointLightRenderer : public Shader
{
private:
	GLuint mvp_matrix;
	GLuint inv_proj_matrix; // inverse projection matrix
	GLuint light_position; // light position in eye space
	GLuint light_color;
	GLuint diffuse_texture;
	GLuint normal_texture;
	GLuint depth_texture;
	GLuint screen_size;

    const DSFramebuffer* framebuffer;
    
public:
	PointLightRenderer() {}
	void load(const DSFramebuffer& fbo);
	void render(const PointLight& light);
	void destroy();
};

#endif
