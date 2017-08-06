#ifndef LEVEL_RENDERER_H
#define LEVEL_RENDERER_H

#include "GL.h"
#include "Path.h"
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "DSFramebuffer.h"

class _SceneRenderer : public Shader
{
private:
	GLuint vertex_matrices;
	GLuint normal_matrices;
	GLuint textures[SCENE_MAX_TEXTURES];

public:
	_SceneRenderer() {}

	void initalize();
	void render(const Scene& scene);
	void destroy();
};

extern _SceneRenderer SceneRenderer;

#endif
