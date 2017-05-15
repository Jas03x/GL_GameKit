//
//  Mesh.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>

#include <vector>

#include "GL.h"
#include "GLM.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Mesh
{
private:
    GLuint vao;
    GLuint vbo;
    Texture texture;
    unsigned int vertex_count;
    
public:
    glm::mat4 model_matrix;
    
    Mesh(){}
    
    void load(const char* source, const char* texture);
    inline void bind() const { glBindVertexArray(this->vao); }
    inline const Texture& getTexture() const { return this->texture; }
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    void destroy();
};

#endif /* Mesh_hpp */
