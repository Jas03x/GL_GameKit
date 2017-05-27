//
//  FrameRenderer.cpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "FrameRenderer.h"

void FrameRenderer::load()
{
    ShaderSource source = ShaderSource(INT_SHDR("frame.vert"), INT_SHDR("frame.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->link(source);
    this->tex = this->getUniform("tex");
}

void FrameRenderer::render(GLuint texture_id)
{
    this->bind();
    Quad::bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(this->tex, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameRenderer::destroy()
{
    Shader::destroy();
}
