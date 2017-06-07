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

class StaticMeshRenderer : public Shader
{
private:
    GLuint texture_id;
    GLuint camera_matrix;
    
public:
    StaticMeshRenderer(){}
    void load();
    void render(const StaticMesh& mesh);
    void destroy();
};

#endif /* StaticMeshRenderer_hpp */
