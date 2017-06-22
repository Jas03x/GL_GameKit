//
//  ParticleBuffer.cpp
//  RoughRocket
//
//  Created by Jas S on 2017-04-28.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "ParticleBuffer.h"

void ParticleBuffer::genVertexArrays(int max_particles)
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, Quad::getVBO());
    glEnableVertexAttribArray(0); // quad vertices
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // Initialize with empty (NULL) buffer : it will be updated later, each frame.
    glBufferData(GL_ARRAY_BUFFER, max_particles * 3 * sizeof(float), NULL, GL_STREAM_DRAW);
    glEnableVertexAttribArray(1); // positions
    glEnableVertexAttribArray(2); // texture indices
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) (0));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) (sizeof(float) * 2));
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleBuffer::destroy()
{
    if(glIsBuffer(this->VBO) == GL_TRUE) glDeleteBuffers(1, &this->VBO);
    if(glIsVertexArray(this->VAO) == GL_TRUE) glDeleteVertexArrays(1, &this->VAO);
    this->texture.destroy();
}
