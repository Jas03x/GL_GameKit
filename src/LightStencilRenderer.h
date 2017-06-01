#ifndef LIGHT_STENCIL_RENDERER_H
#define LIGHT_STENCIL_RENDERER_H

#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "PointLight.h"

class LightStencilRenderer : public Shader
{
private:
    GLuint mvp;
    
public:
    LightStencilRenderer(){}
    void load();
    void render(const PointLight& light);
    void destroy();
};

#endif
