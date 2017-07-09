//
//  Mesh.h
//  CarDemo
//
//  Created by Jas S on 2017-07-07.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include "GL.h"
#include "Math3d.h"
#include "Transform.h"

class Mesh
{
protected:
    GLuint vao;
    GLuint vbo;
    unsigned int vertex_count;
    
    glm::vec3 scale;
    
public:
    Transform transformation;
    
    Mesh(){}
    void destroy();
    
    void bind() const { glBindVertexArray(this->vao); }
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    inline glm::mat4 getMatrix() const { return this->transformation.toMatrix() * glm::scale(this->scale); }
};

#endif /* Mesh_h */
