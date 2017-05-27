//
//  GBlurRenderer.cpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "GBlurRenderer.h"

void GBlurRenderer::init(float width, float height)
{
    ShaderSource source = ShaderSource(INTERNAL("gblur.vert"), INTERNAL("gblur.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->link(source);
    this->tex = this->getUniform("tex");
    this->width = this->getUniform("width");
    this->direction = this->getUniform("direction");
    
    this->screen_size = glm::vec2(width, height);
}

void GBlurRenderer::horizontal_blur(GLuint texture_id)
{
    this->bind();
    Quad::bind();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(this->tex, 0);
    
    glUniform1f(this->width, this->screen_size.x);
    static const float HORIZONTAL_DIRECTION[2] = {1.0f, 0.0f};
    glUniform2fv(this->direction, 1, HORIZONTAL_DIRECTION);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GBlurRenderer::vertical_blur(GLuint texture_id)
{
    this->bind();
    Quad::bind();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(this->tex, 0);
    
    glUniform1f(this->width, this->screen_size.y);
    static const float VERTICAL_DIRECTION[2] = {0.0f, 1.0f};
    glUniform2fv(this->direction, 1, VERTICAL_DIRECTION);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GBlurRenderer::destroy()
{
    Shader::destroy();
}

