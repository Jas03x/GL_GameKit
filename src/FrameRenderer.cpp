//
//  FrameRenderer.cpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "FrameRenderer.hpp"

void FrameRenderer::init()
{
    ShaderSource source = ShaderSource("/Users/Jas/Documents/RoughRocket/RoughRocket/Shaders/frame.vert", "/Users/Jas/Documents/RoughRocket/RoughRocket/Shaders/frame.frag");
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
