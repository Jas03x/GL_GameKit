//
//  RigidBody.h
//  CarDemo
//
//  Created by Jas S on 2017-07-02.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef RigidBody_h
#define RigidBody_h

#include "Collider.h"
#include "PhysicsConfiguration.h"

class RigidBody : public Collider
{
protected:
    btCollisionShape* shape;
    btDefaultMotionState* motion_state;
    
    void bind();
    void unbind();
    
public:
    RigidBody(Transform* _transformation = NULL);
    ~RigidBody();
};

#endif /* RigidBody_h */
