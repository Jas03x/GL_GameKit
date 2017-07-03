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

#include "Math3d.h"
#include "PhysicsConfiguration.h"

class Collider
{
protected:
    btCollisionObject* body;
    
    virtual void bind() = 0;
    virtual void unbind() = 0;
    
public:
    enum Type
    {
        NULL_COLLIDER = 0,
        SOFT_BODY = 1,
        PLANE_COLLIDER = 2
    };
    
    Collider();
    virtual ~Collider();
    
    inline const btCollisionObject* getCollisionObject() const { return this->body; }
    
    void rotate(const glm::quat& rotation);
    void translate(const glm::vec3& translation);
    void transform(const glm::vec3& translation, const glm::quat& rotation);
};

#endif /* Collider_h */
