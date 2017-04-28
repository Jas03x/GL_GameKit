//
//  Quad.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Quad.h"

const float Quad::DATA[12] =
{
    // top triangle
    1.0f,  1.0f, // top right
    -1.0f,  1.0f, // top left
    -1.0f, -1.0f, // bottom left
    // bottom triangle:
    1.0f,  1.0f, // top right
    -1.0f, -1.0f, // bottom left
    1.0f, -1.0f  // bottom right
};

GLuint Quad::_VAO = 0;
GLuint Quad::_VBO = 0;

void Quad::init()
{
    glGenVertexArrays(1, &Quad::_VAO);
    glGenBuffers(1, &Quad::_VBO);
    
    glBindVertexArray(Quad::_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Quad::_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::DATA), Quad::DATA, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Quad::bind()
{
    glBindVertexArray(Quad::_VAO);
}

void Quad::destroy()
{
    if(glIsBuffer(Quad::_VBO) == GL_TRUE) glDeleteBuffers(1, &Quad::_VBO);
    if(glIsVertexArray(Quad::_VAO) == GL_TRUE) glDeleteVertexArrays(1, &Quad::_VAO);
}
