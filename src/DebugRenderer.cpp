//
//  DebugRenderer.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DebugRenderer.h"

_DebugRenderer DebugRenderer;

void _DebugRenderer::initalize(const DebugDrawer *_drawer)
{
    ShaderSource source = ShaderSource("/Users/jass/Documents/Libraries/GL_3D_Engine/src/Shaders/debug.vert", "/Users/jass/Documents/Libraries/GL_3D_Engine/src/Shaders/debug.frag");
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindFragDataLocation(DSFramebuffer::DIFFUSE_TEXTURE, "diffuse_out");
    this->link(source);
    this->vp_matrix = this->getUniform("vp_matrix");
    this->drawer = _drawer;
}

void _DebugRenderer::render()
{
    this->bind();
    this->drawer->bind();
    glUniformMatrix4fv(this->vp_matrix, 1, GL_FALSE, &Camera::getMatrix()[0][0]);
    glDisable(GL_DEPTH_TEST);
    printf("Draw %i\n", this->drawer->getElementCount());
    glDrawArrays(GL_LINES, 0, this->drawer->getElementCount());
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

void _DebugRenderer::destroy()
{
    Shader::destroy();
}
