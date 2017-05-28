#include "LightEngine.h"

std::vector<PointLight> LightEngine::point_lights;
PointLightRenderer LightEngine::_pointlight_renderer;
LightStencilRenderer LightEngine::_stencil_renderer;

void LightEngine::initalize(const DSFramebuffer& fbo)
{
    _pointlight_renderer.load(fbo);
    _stencil_renderer.load();
    PointLight::_genVAO();
}

void LightEngine::insert(const PointLight& point_light)
{
	point_lights.push_back(point_light);
}

void LightEngine::render()
{
    // stencil optimization from: http://ogldev.atspace.co.uk/www/tutorial37/tutorial37.html
    
    glEnable(GL_STENCIL_TEST);
    for (unsigned int i = 0; i < LightEngine::point_lights.size(); i++)
    {
        glClear(GL_STENCIL_BUFFER_BIT);
        
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glStencilFunc(GL_ALWAYS, 0, 0);
        glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
        glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
        glDrawBuffer(GL_NONE);
        _stencil_renderer.render(point_lights[i]);
        
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDisable(GL_DEPTH_TEST);
        glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + DSFramebuffer::LIGHT_TEXTURE);
        _pointlight_renderer.render(point_lights[i]);
    }
    
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
}

void LightEngine::destroy()
{
    PointLight::_deleteVAO();
    _pointlight_renderer.destroy();
    _stencil_renderer.destroy();
}
