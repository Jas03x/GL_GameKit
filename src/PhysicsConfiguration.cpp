//
//  PhysicsConfiguration.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PhysicsConfiguration.h"

btBroadphaseInterface*							PhysicsConfiguration::broadphase;
btDefaultCollisionConfiguration*				PhysicsConfiguration::collision_configuration;
//btSoftBodyRigidBodyCollisionConfiguration*	PhysicsConfiguration::collision_configuration;
btCollisionDispatcher*							PhysicsConfiguration::dispatcher;
btSequentialImpulseConstraintSolver*			PhysicsConfiguration::solver;
btDiscreteDynamicsWorld*						PhysicsConfiguration::dynamics_world;
//btSoftRigidDynamicsWorld*						PhysicsConfiguration::dynamics_world;
//btSoftBodyWorldInfo							PhysicsConfiguration::softbody_info;

void PhysicsConfiguration::initalize(const glm::vec3& gravity)
{
    // setting up the bullet physics dynamics world
    PhysicsConfiguration::broadphase = new btDbvtBroadphase();
    //PhysicsConfiguration::collision_configuration = new btSoftBodyRigidBodyCollisionConfiguration();
    PhysicsConfiguration::collision_configuration = new btDefaultCollisionConfiguration();
    PhysicsConfiguration::dispatcher = new btCollisionDispatcher(PhysicsConfiguration::collision_configuration);
    PhysicsConfiguration::solver = new btSequentialImpulseConstraintSolver();
    PhysicsConfiguration::dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    //PhysicsConfiguration::dynamics_world = new btSoftRigidDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
    PhysicsConfiguration::dynamics_world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	
    // setting up the softbody world information
    /*
    PhysicsConfiguration::softbody_info.m_broadphase = broadphase;
    PhysicsConfiguration::softbody_info.m_dispatcher = dispatcher;
    PhysicsConfiguration::softbody_info.m_gravity = dynamics_world->getGravity();
    PhysicsConfiguration::softbody_info.m_sparsesdf.Initialize();
     */

	RigidBodyManager::Initalize(PhysicsConfiguration::dynamics_world);
}

void PhysicsConfiguration::update()
{
    PhysicsConfiguration::dynamics_world->stepSimulation(1 / 60.f, 10);
	RigidBodyManager::UpdateBodies();
	//SoftBodyManager::UpdateBodies();
}

void PhysicsConfiguration::destroy()
{
    delete PhysicsConfiguration::dynamics_world;
    delete PhysicsConfiguration::solver;
    delete PhysicsConfiguration::dispatcher;
    delete PhysicsConfiguration::collision_configuration;
    delete PhysicsConfiguration::broadphase;
}

void PhysicsConfiguration::addRigidBody(RigidBody* rigidbody) {
	
}

void PhysicsConfiguration::removeRigidBody(RigidBody* rigidbody) {
	
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
