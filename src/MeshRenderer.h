//
//  MeshRenderer.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include <stdio.h>

#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

class MeshRenderer : public Shader
{
private:
    GLuint texture_id;
    GLuint camera_matrix;
    
public:
    MeshRenderer(){}
    void load();
    void render(const Mesh& mesh);
    void destroy();
};

#endif /* MeshRenderer_hpp */
