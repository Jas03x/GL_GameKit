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
    this->bindAttributeLocation(3, "m_index");
    this->bindFragDataLocation(0, "diffuse_out");
    this->bindFragDataLocation(1, "normal_out");
    this->bindFragDataLocation(2, "brightness_out");
    this->link(source);
    this->texture_id = this->getUniform("texture_id");
    this->vertex_matrix = this->getUniform("vertex_matrix");
    this->normal_matrix = this->getUniform("normal_matrix");
    this->materials = this->getUniform("materials");
}

void _StaticMeshRenderer::bind()
{
    Shader::bind();
}

void _StaticMeshRenderer::bindMeshInstance(const StaticMeshInstance& instance)
{
    glm::mat4 model_matrix = instance.getMatrix();
    glm::mat4 v_matrix = Camera::getMatrix() * model_matrix;
    glm::mat4 n_matrix = glm::inverse(glm::transpose(Camera::getViewMatrix() * model_matrix));
    glUniformMatrix4fv(this->vertex_matrix, 1, GL_FALSE, &v_matrix[0][0]);
    glUniformMatrix4fv(this->normal_matrix, 1, GL_FALSE, &n_matrix[0][0]);
}

void _StaticMeshRenderer::render(const StaticMesh& mesh, const std::vector<StaticMeshInstance>* instances)
{
    mesh.bind();
    mesh.getTexture().bind(this->texture_id, 0);
    
    glUniform1fv(this->materials, (unsigned int) mesh.getMaterials().size(), &mesh.getMaterials()[0]);
    
    if(instances) {
        for(unsigned int i = 0; i < instances->size(); i++) {
            this->bindMeshInstance((*instances)[i]);
            glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
        }
    } else {
        this->bindMeshInstance(mesh.getDefaultInstance());
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    }
    
    glBindVertexArray(0);
}

void _StaticMeshRenderer::destroy()
{
    Shader::destroy();
}
