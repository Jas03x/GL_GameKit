//
//  PhysicsConfiguration.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PhysicsConfiguration.h"

btBroadphaseInterface*                      PhysicsConfiguration::broadphase;
btDefaultCollisionConfiguration*            PhysicsConfiguration::collision_configuration;
//btSoftBodyRigidBodyCollisionConfiguration*  PhysicsConfiguration::collision_configuration;
btCollisionDispatcher*                      PhysicsConfiguration::dispatcher;
btSequentialImpulseConstraintSolver*        PhysicsConfiguration::solver;
btDiscreteDynamicsWorld*                    PhysicsConfiguration::dynamics_world;
//btSoftRigidDynamicsWorld*                   PhysicsConfiguration::dynamics_world;
//btSoftBodyWorldInfo                         PhysicsConfiguration::softbody_info;

std::vector<Collider*>                      PhysicsConfiguration::colliders;

void PhysicsConfiguration::initalize()
{
    // setting up the bullet physics dynamics world
    PhysicsConfiguration::broadphase = new btDbvtBroadphase();
    //PhysicsConfiguration::collision_configuration = new btSoftBodyRigidBodyCollisionConfiguration();
    PhysicsConfiguration::collision_configuration = new btDefaultCollisionConfiguration();
    PhysicsConfiguration::dispatcher = new btCollisionDispatcher(PhysicsConfiguration::collision_configuration);
    PhysicsConfiguration::solver = new btSequentialImpulseConstraintSolver();
    PhysicsConfiguration::dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    //PhysicsConfiguration::dynamics_world = new btSoftRigidDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    PhysicsConfiguration::dynamics_world->setGravity(btVector3(0, 10, 0));
    
    // setting up the softbody world information
    /*
    PhysicsConfiguration::softbody_info.m_broadphase = broadphase;
    PhysicsConfiguration::softbody_info.m_dispatcher = dispatcher;
    PhysicsConfiguration::softbody_info.m_gravity = dynamics_world->getGravity();
    PhysicsConfiguration::softbody_info.m_sparsesdf.Initialize();
     */
}

void PhysicsConfiguration::update()
{
    PhysicsConfiguration::dynamics_world->stepSimulation(1 / 60.f, 10);
    for(unsigned int i = 0; i < colliders.size(); i++) {
        if(colliders[i]->hasTransformationPointer()) {
            // printf("Update %i of %i\n", i, (int) colliders.size());
            colliders[i]->updateTransformationPointer();
        }
    }
}

void PhysicsConfiguration::destroy()
{
    delete PhysicsConfiguration::dynamics_world;
    delete PhysicsConfiguration::solver;
    delete PhysicsConfiguration::dispatcher;
    delete PhysicsConfiguration::collision_configuration;
    delete PhysicsConfiguration::broadphase;
}

void PhysicsConfiguration::addCollider(Collider *collider)
{
    PhysicsConfiguration::colliders.push_back(collider);
}

void PhysicsConfiguration::removeCollider(Collider *collider)
{
    std::vector<Collider*>::const_iterator it = std::find(colliders.begin(), colliders.end(), collider);
    if(it != colliders.end()) colliders.erase(it);
}

void PhysicsConfiguration::addRigidBody(Collider* collider) {
    PhysicsConfiguration::addCollider(collider);
    PhysicsConfiguration::dynamics_world->addRigidBody((btRigidBody*) collider->getCollisionObject());
}

void PhysicsConfiguration::removeRigidBody(Collider* collider) {
    PhysicsConfiguration::removeCollider(collider);
    PhysicsConfiguration::dynamics_world->removeRigidBody((btRigidBody*) collider->getCollisionObject());
}

/*
void PhysicsConfiguration::addSoftBody(Collider* collider) {
    PhysicsConfiguration::addCollider(collider);
    PhysicsConfiguration::dynamics_world->addSoftBody((btSoftBody*) collider->getCollisionObject());
}

void PhysicsConfiguration::removeSoftBody(Collider* collider) {
    PhysicsConfiguration::removeCollider(collider);
    PhysicsConfiguration::dynamics_world->removeSoftBody((btSoftBody*) collider->getCollisionObject());
}
 */
