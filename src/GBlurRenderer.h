//
//  GBlurRenderer.hpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef GBlurRenderer_hpp
#define GBlurRenderer_hpp

#include <stdio.h>

#include "GL.h"
#include "GLM.h"
#include "Quad.h"
#include "Shader.h"

class GBlurRenderer : public Shader
{
private:
    GLuint tex;
    GLuint width;
    GLuint direction;
    
    glm::vec2 screen_size;
public:
    GBlurRenderer(){}
    void init(float screen_width, float screen_height);
    void horizontal_blur(GLuint texture_id);
    void vertical_blur(GLuint texture_id);
    void destroy();
};

#endif /* GBlurRenderer_hpp */
