#ifndef LEVEL_RENDERER_H
#define LEVEL_RENDERER_H

#include "GL.h"
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "Framebuffer.h"

class SceneRenderer : public Shader
{
private:
	GLuint vertex_matrices;
	GLuint normal_matrices;
	GLuint textures[SCENE_MAX_TEXTURES];

public:
	SceneRenderer() {}

	void load();
	void render(const Scene& scene);
	void destroy();
};

#endif