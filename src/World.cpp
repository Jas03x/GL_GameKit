//
//  World.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "World.h"

btBroadphaseInterface* World::broadphase;
btDefaultCollisionConfiguration* World::collision_configuration;
btCollisionDispatcher* World::dispatcher;
btSequentialImpulseConstraintSolver* World::solver;
btDiscreteDynamicsWorld* World::world;

void World::init()
{
    broadphase = new btDbvtBroadphase();
    collision_configuration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collision_configuration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    world->setGravity(btVector3(0, -200, 0));
}

void World::addRigidBody(btRigidBody* body)
{
    world->addRigidBody(body);
}

void World::removeRigidBody(btRigidBody* body)
{
    world->removeRigidBody(body);
}

void World::update() { world->stepSimulation(1.0f / 60.0f, 10); }

void World::addDebugDrawer(btIDebugDraw* drawer) { world->setDebugDrawer(drawer); }
void World::debugDraw() { world->debugDrawWorld(); }

void World::destroy()
{
    delete world;
    delete solver;
    delete dispatcher;
    delete collision_configuration;
    delete broadphase;
}
