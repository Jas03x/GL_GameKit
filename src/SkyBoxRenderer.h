#ifndef SKY_BOX_RENDERER_H
#define SKY_BOX_RENDERER_H

#include <vector>

#include "GL.h"
#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "SkyBox.h"
#include "OBJ_Loader.h"
#include "Framebuffer.h"

class _SkyBoxRenderer : public Shader
{
private:
    GLuint matrix,
            skymap;
    GLuint vao, vbo;
    unsigned int vertex_count;
    
public:
    _SkyBoxRenderer(){}
    void initalize();
    void render(const SkyBox& skybox);
    void destroy();
};

extern _SkyBoxRenderer SkyBoxRenderer;

#endif
