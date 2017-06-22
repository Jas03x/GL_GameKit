//
//  DynamicMesh.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DynamicMesh.h"

void DynamicMesh::load(const char* path)
{
    ColladaLoader loader = ColladaLoader(path);
	if (loader.getTextures().size() <= 0 || loader.getTextures().size() > DYNAMIC_MESH_MAX_TEXTURE_COUNT) {
		printf("Invalid texture count [%lu] in collada file [%s].\n", loader.getTextures().size(), path);
		throw -1;
	}
    
    this->textures = new Texture[loader.getTextures().size()];
    std::string file_path = std::string(path);
    file_path = file_path.substr(0, file_path.find_last_of("/\\") + 1);
    for(unsigned int i = 0; i < loader.getTextures().size(); i++)
    {
        std::string t_path = file_path + loader.getTextures()[i];
        this->textures[i].load(t_path.c_str());
    }
    
    size_t vc = loader.getVertices().size();
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vc * 9, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vc * 3, &loader.getVertices()[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 3, sizeof(float) * vc * 3, &loader.getNormals()[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 6, sizeof(float) * vc * 2, &loader.getUVs()[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 8, sizeof(float) * vc, &loader.getTextureIndices()[0]);
    
    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // normals
    glEnableVertexAttribArray(2); // uvs
    glEnableVertexAttribArray(3); // texture ids
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 6));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 8));
	// INSERT BONE DATA HERE
	// SLOT 4 = index
	// SLOT 5 = weight
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->texture_count = (unsigned int) loader.getTextures().size();
    this->vertex_count = (unsigned int) loader.getVertices().size();
    this->position = glm::vec3(0);
    this->scale = glm::vec3(1);
    this->rotation = glm::quat(0, 0, 0, 1);
}

void DynamicMesh::destroy()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    
    for(unsigned int i = 0; i < this->texture_count; i++) this->textures[i].destroy();
    if(this->textures != NULL) delete[] this->textures;
}
