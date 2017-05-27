//
//  FrameRenderer.hpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef FrameRenderer_hpp
#define FrameRenderer_hpp

#include <stdio.h>

#include "GL.h"
#include "GLM.h"
#include "Quad.h"
#include "Shader.h"

class FrameRenderer : public Shader
{
private:
    GLuint tex;
public:
    FrameRenderer(){}
    void load();
    void render(GLuint texture_id);
    void destroy();
};

#endif /* FrameRenderer_hpp */
