//
//  Character.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Character.h"

void Character::load(const char* path, const char* name)
{
	std::string source = std::string(path) + name;
    ColladaLoader loader = ColladaLoader(source.c_str());
	if (loader.getTextures().size() != 1) {
		printf("Invalid texture count [%lu] in collada file [%s].\n", loader.getTextures().size(), source.c_str());
		throw -1;
	}
	std::string t_path = std::string(path) + *loader.getTextures().begin();
    this->texture.load(t_path.c_str());
    
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
	// INSERT BONE DATA HERE
	// SLOT 3 = index
	// SLOT 4 = weight
    
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
