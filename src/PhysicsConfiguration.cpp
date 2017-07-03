//
//  PhysicsConfiguration.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PhysicsConfiguration.h"

btBroadphaseInterface*                      PhysicsConfiguration::broadphase;
//btDefaultCollisionConfiguration*          PhysicsConfiguration::collision_configuration;
btSoftBodyRigidBodyCollisionConfiguration*  PhysicsConfiguration::collision_configuration;
btCollisionDispatcher*                      PhysicsConfiguration::dispatcher;
btSequentialImpulseConstraintSolver*        PhysicsConfiguration::solver;
//btDiscreteDynamicsWorld*                  PhysicsConfiguration::dynamics_world;
btSoftRigidDynamicsWorld*                   PhysicsConfiguration::dynamics_world;
btSoftBodyWorldInfo                         PhysicsConfiguration::softbody_info;


void PhysicsConfiguration::initalize()
{
    // setting up the bullet physics dynamics world
    PhysicsConfiguration::broadphase = new btDbvtBroadphase();
    PhysicsConfiguration::collision_configuration = new btSoftBodyRigidBodyCollisionConfiguration();
    PhysicsConfiguration::dispatcher = new btCollisionDispatcher(PhysicsConfiguration::collision_configuration);
    PhysicsConfiguration::solver = new btSequentialImpulseConstraintSolver();
    PhysicsConfiguration::dynamics_world = new btSoftRigidDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    PhysicsConfiguration::dynamics_world->setGravity(btVector3(0, -10, 0));
    
    // setting up the softbody world information
    PhysicsConfiguration::softbody_info.m_broadphase = broadphase;
    PhysicsConfiguration::softbody_info.m_dispatcher = dispatcher;
    PhysicsConfiguration::softbody_info.m_gravity = dynamics_world->getGravity();
    PhysicsConfiguration::softbody_info.m_sparsesdf.Initialize();
}

void PhysicsConfiguration::update()
{
    PhysicsConfiguration::dynamics_world->stepSimulation(1 / 60.f, 10);
}

void PhysicsConfiguration::destroy()
{
    delete PhysicsConfiguration::dynamics_world;
    delete PhysicsConfiguration::solver;
    delete PhysicsConfiguration::dispatcher;
    delete PhysicsConfiguration::collision_configuration;
    delete PhysicsConfiguration::broadphase;
}

void PhysicsConfiguration::addRigidBody(btRigidBody* body) { PhysicsConfiguration::dynamics_world->addRigidBody(body); }
void PhysicsConfiguration::addSoftBody(btSoftBody* body) { PhysicsConfiguration::dynamics_world->addSoftBody(body); }
void PhysicsConfiguration::removeRigidBody(btRigidBody* body) { PhysicsConfiguration::dynamics_world->removeRigidBody(body); }
void PhysicsConfiguration::removeSoftBody(btSoftBody* body) { PhysicsConfiguration::dynamics_world->removeSoftBody(body); }
