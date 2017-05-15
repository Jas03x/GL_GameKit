//
//  MeshRenderer.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "MeshRenderer.h"

void MeshRenderer::load()
{
    ShaderSource source = ShaderSource("/Users/Jas/Documents/GameKit/src/Shaders/mesh.vert", "/Users/Jas/Documents/GameKit/src/Shaders/mesh.frag");
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindAttributeLocation(1, "normal");
    this->bindAttributeLocation(2, "uv");
    this->link(source);
    this->texture_id = this->getUniform("texture_id");
    this->camera_matrix = this->getUniform("camera_matrix");
}

void MeshRenderer::render(const Mesh &mesh)
{
    this->bind();
    mesh.bind();
    mesh.getTexture().bind(this->texture_id, 0);
    glm::mat4 matrix = Camera::vp * mesh.model_matrix;
    glUniformMatrix4fv(this->camera_matrix, 1, GL_FALSE, &matrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    glBindVertexArray(0);
}

void MeshRenderer::destroy()
{
    Shader::destroy();
}
