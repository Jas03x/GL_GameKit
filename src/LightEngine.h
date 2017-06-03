#ifndef LIGHT_ENGINE_H
#define LIGHT_ENGINE_H

#include <vector>

#include "GL.h"
#include "Math3d.h"
#include "OBJ_Loader.h"
#include "PointLight.h"
#include "Framebuffer.h"
#include "PointLightRenderer.h"
#include "LightStencilRenderer.h"

namespace LightEngine
{
	extern std::vector<PointLight> point_lights;
    extern PointLightRenderer _pointlight_renderer;
    extern LightStencilRenderer _stencil_renderer;

	void initalize(const DSFramebuffer& fbo);
	void insert(const PointLight& point_light);
    void render();
	void destroy();
}

#endif
