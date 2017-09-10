//
//  Collider.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Collider_h
#define Collider_h

#include <BulletCollision/btBulletCollisionCommon.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision\CollisionShapes\btShapeHull.h>
#include <BulletCollision\CollisionShapes\btConvexHullShape.h>

#include "Math3d.h"
#include "Transform.h"
#include "MeshDescriptor.h"
#include "VectorTree.h"

class Collider
{
protected:
    btCollisionShape* shape;
    
public:
    enum Type
    {
        NULL_COLLIDER = 0,
        SOFT_BODY = 1,
        PLANE_COLLIDER = 2
    };
    
    Collider();
    virtual ~Collider();
    
    inline const btCollisionShape* getCollisionShape() const { return this->shape; }
	inline btCollisionShape* getCollisionShape() { return this->shape; }
};

#endif /* Collider_h */
