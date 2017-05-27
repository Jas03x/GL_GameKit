//
//  DebugDrawer.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DebugDrawer.h"


DebugDrawer::DebugDrawer()
{
    ShaderSource source = ShaderSource(INT_SHDR("debug.vert"), INT_SHDR("debug.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->link(source);
    this->matrix = this->getUniform("matrix");
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, P_DEBUG_MAX_BUFFER_LENGTH * sizeof(float), NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->debug_mode = btIDebugDraw::DebugDrawModes::DBG_DrawWireframe;
    this->vertex_count = 0;
}

DebugDrawer::~DebugDrawer()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
    /*this->vertex_buffer.push_back(from.getX());
    this->vertex_buffer.push_back(from.getY());
    this->vertex_buffer.push_back(from.getZ());
    
    this->vertex_buffer.push_back(to.getX());
    this->vertex_buffer.push_back(to.getY());
    this->vertex_buffer.push_back(to.getZ());*/
    this->vertex_buffer.insert(this->vertex_buffer.end(), &from[0], &from[0] + 3);
    this->vertex_buffer.insert(this->vertex_buffer.end(), &to[0], &to[0] + 3);
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &fromColor, const btVector3 &toColor)
{
    /*this->vertex_buffer.push_back(from.getX());
    this->vertex_buffer.push_back(from.getY());
    this->vertex_buffer.push_back(from.getZ());
    
    this->vertex_buffer.push_back(to.getX());
    this->vertex_buffer.push_back(to.getY());
    this->vertex_buffer.push_back(to.getZ());*/
    this->vertex_buffer.insert(this->vertex_buffer.end(), &from[0], &from[0] + 3);
    this->vertex_buffer.insert(this->vertex_buffer.end(), &to[0], &to[0] + 3);
}

void DebugDrawer::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color){}

void DebugDrawer::reportErrorWarning (const char *warningString)
{
    printf("Bullet error/warning: %s\n", warningString);
}

void DebugDrawer::draw3dText (const btVector3 &location, const char *textString){}

void DebugDrawer::setDebugMode(int debugMode)
{
    //this->debug_mode = debugMode;
}

int DebugDrawer::getDebugMode () const
{
    return this->debug_mode;
}

void DebugDrawer::flushLines()
{
    if(this->vertex_buffer.size() >= P_DEBUG_MAX_BUFFER_LENGTH)
    {
        puts("Error: P_DEBUG_MAX_BUFFER_LENGTH exceeded.");
        throw -1;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, P_DEBUG_MAX_BUFFER_LENGTH * sizeof(float), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * this->vertex_buffer.size(), &this->vertex_buffer[0]);
    this->vertex_count = this->vertex_buffer.size() / 3;
    
    this->vertex_buffer.clear();
}

void DebugDrawer::draw()
{
    this->bind();
    glBindVertexArray(this->vao);
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &Camera::vp[0][0]);
    glDrawArrays(GL_LINES, 0, (GLsizei) this->vertex_count);
    glBindVertexArray(0);
}

