#ifndef LIGHT_STENCIL_RENDERER_H
#define LIGHT_STENCIL_RENDERER_H

#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "PointLight.h"

class _LightStencilRenderer : public Shader
{
private:
    GLuint mvp;
    
public:
    _LightStencilRenderer(){}
    void initalize();
    void render(const PointLight& light);
    void destroy();
};

extern _LightStencilRenderer LightStencilRenderer;

#endif
