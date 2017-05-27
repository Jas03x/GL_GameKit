//
//  DebugDrawer.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DebugDrawer_hpp
#define DebugDrawer_hpp

#include <stdio.h>


#include <vector>

#include "GL.h"
#include "Camera.h"
#include "Shader.h"
#include <LinearMath/btIDebugDraw.h>

#define P_DEBUG_MAX_BUFFER_LENGTH 1000000

class DebugDrawer : public btIDebugDraw, public Shader
{
private:
    int debug_mode;
    unsigned long vertex_count;
    std::vector<float> vertex_buffer;
    
    GLuint vao, vbo;
    GLuint matrix;
    
public:
    DebugDrawer();
    ~DebugDrawer();
    
    //DefaultColors 	getDefaultColors () const;
    //void 	setDefaultColors (const DefaultColors &);
    void 	drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color);
    void 	drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &fromColor, const btVector3 &toColor);
    //void 	drawSphere (btScalar radius, const btTransform &transform, const btVector3 &color);
    //void 	drawSphere (const btVector3 &p, btScalar radius, const btVector3 &color);
    //void 	drawTriangle (const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &, const btVector3 &, const btVector3 &, const btVector3 &color, btScalar alpha);
    //void 	drawTriangle (const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &color, btScalar);
    void 	drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
    void 	reportErrorWarning (const char *warningString);
    void 	draw3dText (const btVector3 &location, const char *textString);
    void 	setDebugMode (int debugMode);
    int 	getDebugMode () const;
    //void 	drawAabb (const btVector3 &from, const btVector3 &to, const btVector3 &color);
    //void 	drawTransform (const btTransform &transform, btScalar orthoLen);
    //void 	drawArc (const btVector3 &center, const btVector3 &normal, const btVector3 &axis, btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle, const btVector3 &color, bool drawSect, btScalar stepDegrees=btScalar(10.f));
    //void 	drawSpherePatch (const btVector3 &center, const btVector3 &up, const btVector3 &axis, btScalar radius, btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3 &color, btScalar stepDegrees=btScalar(10.f), bool drawCenter=true);
    //void 	drawBox (const btVector3 &bbMin, const btVector3 &bbMax, const btVector3 &color);
    //void 	drawBox (const btVector3 &bbMin, const btVector3 &bbMax, const btTransform &trans, const btVector3 &color);
    //void 	drawCapsule (btScalar radius, btScalar halfHeight, int upAxis, const btTransform &transform, const btVector3 &color);
    //void 	drawCylinder (btScalar radius, btScalar halfHeight, int upAxis, const btTransform &transform, const btVector3 &color);
    //void 	drawCone (btScalar radius, btScalar height, int upAxis, const btTransform &transform, const btVector3 &color);
    //void 	drawPlane (const btVector3 &planeNormal, btScalar planeConst, const btTransform &transform, const btVector3 &color);
    void 	flushLines ();
    
    void    draw();
};


#endif /* DebugDrawer_hpp */
