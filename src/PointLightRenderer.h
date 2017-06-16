#ifndef POINT_LIGHT_RENDERER_H
#define POINT_LIGHT_RENDERER_H

#include "GL.h"
#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "PointLight.h"
#include "Framebuffer.h"

class _PointLightRenderer : public Shader
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
	_PointLightRenderer() {}
	void initalize(const DSFramebuffer& fbo);
	void render(const PointLight& light);
	void destroy();
};

extern _PointLightRenderer PointLightRenderer;

#endif
