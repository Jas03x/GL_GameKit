//
//  DebugRenderer.h
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DebugRenderer_h
#define DebugRenderer_h

#include "GL.h"
#include "Path.h"
#include "Math3d.h"
#include "Shader.h"
#include "Camera.h"
#include "DebugDrawer.h"
#include "Framebuffer.h"

class _DebugRenderer : public Shader
{
private:
    GLuint vp_matrix;
    const DebugDrawer* drawer;
    
public:
    _DebugRenderer(){}
    void initalize(const DebugDrawer* _drawer);
    void render();
    void destroy();
};

extern _DebugRenderer DebugRenderer;

#endif /* DebugRenderer_h */
