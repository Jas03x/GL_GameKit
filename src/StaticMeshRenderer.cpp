//
//  StaticMeshRenderer.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "StaticMeshRenderer.h"

_StaticMeshRenderer StaticMeshRenderer;

void _StaticMeshRenderer::initalize()
{
    ShaderSource source = ShaderSource(INT_SHDR("mesh.vert"), INT_SHDR("mesh.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindAttributeLocation(1, "normal");
    this->bindAttributeLocation(2, "uv");
    this->bindFragDataLocation(DSFramebuffer::DIFFUSE_TEXTURE, "diffuse_out");
    this->bindFragDataLocation(DSFramebuffer::NORMAL_TEXTURE, "normal_out");
    this->bindFragDataLocation(DSFramebuffer::LIGHT_TEXTURE, "light_out");
    this->link(source);
    this->texture_id = this->getUniform("texture_id");
    this->camera_matrix = this->getUniform("camera_matrix");
}

void _StaticMeshRenderer::bind()
{
    Shader::bind();
}

void _StaticMeshRenderer::render(const StaticMesh& mesh)
{
    mesh.bind();
    mesh.getTexture().bind(this->texture_id, 0);
    glm::mat4 matrix = Camera::getMatrix() * mesh.model_matrix;
    glUniformMatrix4fv(this->camera_matrix, 1, GL_FALSE, &matrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    glBindVertexArray(0);
}

void _StaticMeshRenderer::destroy()
{
    Shader::destroy();
}
