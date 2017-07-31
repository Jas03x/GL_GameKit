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

typedef struct Mesh
{
protected:
    GLuint vao;
    GLuint vbo;
    unsigned int vertex_count;
    
public:
    Mesh(){}
    void bind() const { glBindVertexArray(this->vao); }
    void destroy();
    
    inline unsigned int getVertexCount() const { return this->vertex_count; }
}Mesh;

#endif /* Mesh_h */
