//
//  DebugDrawer.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DebugDrawer.h"

DebugDrawer::DebugDrawer()
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * DEBUG_DRAWER_STARTING_BUFFER_SIZE, NULL, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(0); // vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    this->vbo_size = DEBUG_DRAWER_STARTING_BUFFER_SIZE;
    this->vertex_data.reserve(DEBUG_DRAWER_STARTING_BUFFER_SIZE);
    this->element_count = 0;
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    PhysicsConfiguration::dynamics_world->setDebugDrawer(this);
}

DebugDrawer::~DebugDrawer()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    this->vertex_data.push_back(glm::vec3(from.getX(), from.getY(), from.getZ()));
    this->vertex_data.push_back(glm::vec3(to.getX(), to.getY(), to.getZ()));
}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
    this->vertex_data.push_back(glm::vec3(from.getX(), from.getY(), from.getZ()));
    this->vertex_data.push_back(glm::vec3(to.getX(), to.getY(), to.getZ()));
}

void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    // not implemented
}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
    printf("Bullet physics debug drawer warning: %s\n", warningString);
}

void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
    // not implemented
}

void DebugDrawer::setDebugMode(int debugMode)
{
    // not implemented yet
}

int DebugDrawer::getDebugMode() const
{
    return DBG_DrawWireframe; // OR with other constants for more data
}

void DebugDrawer::flushLines()
{
    if(this->vertex_data.size() > this->vbo_size) {
        this->vbo_size = (unsigned int) this->vertex_data.size();
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->vbo_size, NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * this->vertex_data.size(), &this->vertex_data[0][0]);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * this->vertex_data.size(), &this->vertex_data[0][0]);
    }
    this->element_count = (unsigned int) this->vertex_data.size();
    this->vertex_data.clear();
}

void DebugDrawer::update()
{
    PhysicsConfiguration::dynamics_world->debugDrawWorld();
}
