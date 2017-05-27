//
//  CharacterRenderer.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CharacterRenderer.h"

void CharacterRenderer::load()
{
    ShaderSource source = ShaderSource(INTERNAL("character.vert"), INTERNAL("character.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindAttributeLocation(1, "normal");
    this->bindAttributeLocation(2, "uv");
	this->bindFragDataLocation(DSFramebuffer::DIFFUSE_TEXTURE, "diffuse_out");
	this->bindFragDataLocation(DSFramebuffer::NORMAL_TEXTURE, "normal_out");
	this->bindFragDataLocation(DSFramebuffer::LIGHT_TEXTURE, "light_out");
    this->link(source);
    this->texture_id = this->getUniform("texture_id");
    this->vertex_matrix = this->getUniform("vertex_matrix");
	this->normal_matrix = this->getUniform("normal_matrix");
}

void CharacterRenderer::render(const Character& character)
{
    this->bind();
    character.bind();
    character.getTexture().bind(this->texture_id, 0);
    
    glm::mat4 vmatrix = Camera::vp * character.model_matrix;
	glm::mat4 nmatrix = glm::inverse(glm::transpose(Camera::view * character.model_matrix));
    glUniformMatrix4fv(this->vertex_matrix, 1, GL_FALSE, &vmatrix[0][0]);
	glUniformMatrix4fv(this->normal_matrix, 1, GL_FALSE, &nmatrix[0][0]);
    
    glDrawArrays(GL_TRIANGLES, 0, character.getVertexCount());
    glBindVertexArray(0); // unbind the character's vao
}

void CharacterRenderer::destroy()
{
    Shader::destroy();
}
