//
//  Mesh.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "StaticMesh.h"

StaticMesh::StaticMesh(GLuint _vao, GLuint _vbo, const char* _texture, unsigned int _vertex_count)
{
	this->vao = _vao;
	this->vbo = _vbo;
	this->texture.load(_texture);
	this->vertex_count = _vertex_count;
}

void StaticMesh::load(const char* source, const char* texture)
{
    OBJ_Loader loader = OBJ_Loader(source);
    this->texture.load(texture);
    
    std::vector<float> vertex_buffer;
    vertex_buffer.reserve(loader.getIndices().size() * 8);
    for(unsigned int i = 0; i < loader.getIndices().size(); i++)
    {
        const glm::uvec3 &index = loader.getIndices().at(i);
        const float* vertex = &loader.getVertices().at(index.x - 1)[0];
        const float* normal = &loader.getNormals().at(index.z - 1)[0];
        const float* uv = &loader.getUVs().at(index.y - 1)[0];
        vertex_buffer.insert(vertex_buffer.end(), vertex, vertex + 3);
        vertex_buffer.insert(vertex_buffer.end(), normal, normal + 3);
        vertex_buffer.insert(vertex_buffer.end(), uv, uv + 2);
    }
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(float), &vertex_buffer[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // vertex
    glEnableVertexAttribArray(1); // normal
    glEnableVertexAttribArray(2); // uv
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (sizeof(float) * 6));
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertex_count = (unsigned int) loader.getIndices().size();
    
    this->scale = glm::vec3(1);
    this->transformation = Transform();
}

void StaticMesh::destroy()
{
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
}
