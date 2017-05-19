//
//  World.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>

#include <vector>

#include <btBulletDynamicsCommon.h>
#include "DebugDrawer.h"

namespace World
{
    extern btBroadphaseInterface* broadphase;
    extern btDefaultCollisionConfiguration* collision_configuration;
    extern btCollisionDispatcher* dispatcher;
    extern btSequentialImpulseConstraintSolver* solver;
    extern btDiscreteDynamicsWorld* world;
    
    void init();
    void addRigidBody(btRigidBody* body);
    void removeRigidBody(btRigidBody* body);
    void update();
    void destroy();
    
    void addDebugDrawer(btIDebugDraw* drawer);
    void debugDraw();
}

#endif /* World_hpp */
