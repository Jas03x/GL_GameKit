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

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/btBulletCollisionCommon.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

#include "Collider.h"

namespace PhysicsConfiguration
{
    extern btBroadphaseInterface* broadphase;
    extern btSoftBodyRigidBodyCollisionConfiguration* collision_configuration;
    extern btCollisionDispatcher* dispatcher;
    extern btSequentialImpulseConstraintSolver* solver;
    extern btSoftRigidDynamicsWorld* dynamics_world;
    extern btSoftBodyWorldInfo softbody_info;
    
    extern std::vector<Collider*> colliders;
    
    void initalize();
    void update();
    void destroy();
    
    void addRigidBody(Collider* collider);
    void addSoftBody(Collider* collider);
    void removeRigidBody(Collider* collider);
    void removeSoftBody(Collider* collider);
    void addCollider(Collider* collider);
    void removeCollider(Collider* collider);
}

#endif /* PhysicsConfiguration_h */
