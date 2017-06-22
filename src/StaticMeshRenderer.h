//
//  StaticMeshRenderer.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef StaticMeshRenderer_hpp
#define StaticMeshRenderer_hpp

#include <stdio.h>

#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "Framebuffer.h"

class _StaticMeshRenderer : public Shader
{
private:
    GLuint texture_id;
    GLuint camera_matrix;
    
public:
    _StaticMeshRenderer(){}
    void initalize();
    void bind();
    void render(const StaticMesh& mesh);
    void destroy();
};

extern _StaticMeshRenderer StaticMeshRenderer;

#endif /* StaticMeshRenderer_hpp */
