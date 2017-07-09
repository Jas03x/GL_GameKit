//
//  Mesh.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-07.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Mesh.h"

void Mesh::destroy()
{
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
}
