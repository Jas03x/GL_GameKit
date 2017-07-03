//
//  PhysicsConfiguration.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef PhysicsConfiguration_h
#define PhysicsConfiguration_h

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/btBulletCollisionCommon.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

namespace PhysicsConfiguration
{
    extern btBroadphaseInterface* broadphase;
    extern btSoftBodyRigidBodyCollisionConfiguration* collision_configuration;
    extern btCollisionDispatcher* dispatcher;
    extern btSequentialImpulseConstraintSolver* solver;
    extern btSoftRigidDynamicsWorld* dynamics_world;
    extern btSoftBodyWorldInfo softbody_info;
    
    void initalize();
    void update();
    void destroy();
    void addRigidBody(btRigidBody* body);
    void addSoftBody(btSoftBody* body);
    void removeRigidBody(btRigidBody* body);
    void removeSoftBody(btSoftBody* body);
}

#endif /* PhysicsConfiguration_h */
