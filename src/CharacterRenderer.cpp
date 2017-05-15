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
    ShaderSource source = ShaderSource("/Users/Jas/Documents/GameKit/src/Shaders/character.vert", "/Users/Jas/Documents/GameKit/src/Shaders/character.frag");
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindAttributeLocation(1, "normal");
    this->bindAttributeLocation(2, "uv");
    this->link(source);
    this->texture_id = this->getUniform("texture_id");
    this->camera_matrix = this->getUniform("camera_matrix");
}

void CharacterRenderer::render(const Character& character)
{
    this->bind();
    character.bind();
    character.getTexture().bind(this->texture_id, 0);
    
    glm::mat4 matrix = Camera::vp * character.model_matrix;
    glUniformMatrix4fv(this->camera_matrix, 1, GL_FALSE, &matrix[0][0]);
    
    glDrawArrays(GL_TRIANGLES, 0, character.getVertexCount());
    glBindVertexArray(0); // unbind the character's vao
}

void CharacterRenderer::destroy()
{
    Shader::destroy();
}
