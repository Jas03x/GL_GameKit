//
//  PhysicsConfiguration.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef PhysicsConfiguration_h
#define PhysicsConfiguration_h

#include <vector>

#include "Physics.h"
#include "RigidBody.h"

namespace PhysicsConfiguration
{
    extern btBroadphaseInterface* broadphase;
    extern btDefaultCollisionConfiguration* collision_configuration;
    //extern btSoftBodyRigidBodyCollisionConfiguration* collision_configuration;
    extern btCollisionDispatcher* dispatcher;
    extern btSequentialImpulseConstraintSolver* solver;
    extern btDiscreteDynamicsWorld* dynamics_world;
    //extern btSoftRigidDynamicsWorld* dynamics_world;
    //extern btSoftBodyWorldInfo softbody_info;
    
    void initalize(const glm::vec3& gravity);
    void update();
    void destroy();
    
    void addRigidBody(RigidBody* rigidbody);
    void removeRigidBody(RigidBody* rigidbody);
    //void addSoftBody(Collider* collider);
    //void removeSoftBody(Collider* collider);
}

#endif /* PhysicsConfiguration_h */
