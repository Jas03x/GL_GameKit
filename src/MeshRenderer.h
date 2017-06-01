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

#include "Mesh.h"
#include "Path.h"
#include "Camera.h"
#include "Shader.h"

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
