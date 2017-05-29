#ifndef SUN_RENDERER_H
#define SUN_RENDERER_H

#include "GL.h"
#include "Sun.h"
#include "Quad.h"
#include "Camera.h"
#include "Shader.h"
#include "Framebuffer.h"

class SunRenderer : public Shader
{
private:
    GLuint sun_position;
    GLuint sun_color;
    GLuint screen_size;
    GLuint inv_proj_matrix;
    
    GLuint diffuse_texture;
    GLuint normal_texture;
    GLuint depth_texture;
    
    const DSFramebuffer* framebuffer;
    
public:
    SunRenderer(){}
    void load(const DSFramebuffer& fbo);
    void render();
    void destroy();
};

#endif
