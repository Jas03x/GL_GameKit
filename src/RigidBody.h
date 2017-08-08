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
    
	void construct(btCollisionShape* shape, const Transform& transform, const float mass, const glm::vec3& inertia);
    void bind();
    void unbind();
    
public:
    RigidBody(Transform* _transformation = NULL);
	RigidBody(btCollisionShape* shape, const Transform& transform, const float mass, const glm::vec3& inertia);
    ~RigidBody();
};

#endif /* RigidBody_h */
