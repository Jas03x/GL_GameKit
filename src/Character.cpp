//
//  Character.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Character.h"

void Character::load(const char* source, const char* texture)
{
    ColladaLoader loader = ColladaLoader(source);
    this->texture.load(texture);
    
    size_t vc = loader.getVertices().size();
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vc * 8, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vc * 3, &loader.getVertices()[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 3, sizeof(float) * vc * 3, &loader.getNormals()[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 6, sizeof(float) * vc * 2, &loader.getUVs()[0][0]);
    
    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // normals
    glEnableVertexAttribArray(2); // uvs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 6));
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertex_count = (unsigned int) loader.getVertices().size();
    this->model_matrix = glm::mat4(1.0f);
}

void Character::destroy()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
}
