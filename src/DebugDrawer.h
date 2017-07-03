//
//  DebugDrawer.h
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DebugDrawer_h
#define DebugDrawer_h

#include <vector>
#include <LinearMath/btIDebugDraw.h>

#include "GL.h"
#include "Math3d.h"
#include "PhysicsConfiguration.h"

#define DEBUG_DRAWER_STARTING_BUFFER_SIZE 2048

class DebugDrawer : public btIDebugDraw
{
private:
    GLuint vao;
    GLuint vbo;
    unsigned int vbo_size;
    unsigned int element_count;
    std::vector<glm::vec3> vertex_data;
    
public:
    // initalization and destruction
    DebugDrawer();
    ~DebugDrawer();
    
    // bullet interface
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    void reportErrorWarning(const char* warningString);
    void draw3dText(const btVector3& location, const char* textString);
    void setDebugMode(int debugMode);
    int	 getDebugMode() const;
    void flushLines();
    
    // custom methods
    void update();
    inline void bind() const { glBindVertexArray(this->vao); }
    inline unsigned int getElementCount() const { return this->element_count; }
};

#endif /* DebugDrawer_h */
