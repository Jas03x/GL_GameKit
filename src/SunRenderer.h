#ifndef SUN_RENDERER_H
#define SUN_RENDERER_H

#include "GL.h"
#include "Sun.h"
#include "Path.h"
#include "Quad.h"
#include "Camera.h"
#include "Shader.h"
#include "DSFramebuffer.h"

class _SunRenderer : public Shader
{
private:
    GLuint sun_position;
    GLuint sun_color;
    GLuint screen_size;
    GLuint inv_proj_matrix;
    
    GLuint diffuse_texture;
    GLuint normal_texture;
    GLuint depth_texture;
    GLuint brightness_texture;
    
    const DSFramebuffer* framebuffer;
    
public:
    _SunRenderer(){}
    void initalize(const DSFramebuffer& fbo);
    void render();
    void destroy();
};

extern _SunRenderer SunRenderer;

#endif
