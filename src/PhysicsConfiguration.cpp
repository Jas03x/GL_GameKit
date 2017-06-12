//
//  PhysicsConfiguration.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PhysicsConfiguration.h"

btBroadphaseInterface* PhysicsConfiguration::broadphase;
btDefaultCollisionConfiguration* PhysicsConfiguration::collision_configuration;
btCollisionDispatcher* PhysicsConfiguration::dispatcher;
btSequentialImpulseConstraintSolver* PhysicsConfiguration::solver;
btDiscreteDynamicsWorld* PhysicsConfiguration::world;

void PhysicsConfiguration::init()
{
    broadphase = new btDbvtBroadphase();
    collision_configuration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collision_configuration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    world->setGravity(btVector3(0, -200, 0));
}

void PhysicsConfiguration::addRigidBody(btRigidBody* body)
{
    world->addRigidBody(body);
}

void PhysicsConfiguration::removeRigidBody(btRigidBody* body)
{
    world->removeRigidBody(body);
}

void PhysicsConfiguration::update() { world->stepSimulation(1.0f / 60.0f, 10); }

void PhysicsConfiguration::addDebugDrawer(btIDebugDraw* drawer) { world->setDebugDrawer(drawer); }
void PhysicsConfiguration::debugDraw() { world->debugDrawWorld(); }

void PhysicsConfiguration::destroy()
{
    delete world;
    delete solver;
    delete dispatcher;
    delete collision_configuration;
    delete broadphase;
}
