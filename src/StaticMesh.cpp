//
//  Mesh.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "StaticMesh.h"

void StaticMesh::construct(const MeshLoader& loader, const glm::vec3& _scale, const GLenum draw_mode)
{
    if(loader.getTextures().size() == 0 || loader.getTextures().size() > STATIC_MESH_MAX_TEXTURE_COUNT) {
        printf("Invalid texture count [%lu] in file %s\n", loader.getTextures().size(), loader.getPath().c_str());
    }
    
    this->texture = Texture(loader.getDirectory() + loader.getTextures()[0]);
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    loader.getVertexArray(vertices);
    loader.getNormalArray(normals);
    loader.getUvArray(uvs);
    size_t vc = loader.getFaces().size();
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vc * 8, NULL, draw_mode);
    
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 0, sizeof(float) * vc * 3, &vertices[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 3, sizeof(float) * vc * 3, &normals[0][0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 6, sizeof(float) * vc * 2, &uvs[0][0]);
    
    glEnableVertexAttribArray(0); // vertex
    glEnableVertexAttribArray(1); // normal
    glEnableVertexAttribArray(2); // uv
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(float) * vc * 0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(float) * vc * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(float) * vc * 6));
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertex_count = (unsigned int) loader.getFaces().size();
    this->scale = _scale;
    this->transformation = Transform();
}

void StaticMesh::destroy()
{
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    
    Mesh::destroy();
}
