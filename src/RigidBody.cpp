//
//  RigidBody.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-02.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "RigidBody.h"

RigidBody::RigidBody(Transform* _transformation) : Collider(_transformation)
{
    this->shape = NULL;
    this->motion_state = NULL;
}

RigidBody::RigidBody(btCollisionShape* shape, const Transform& transform, const float mass, const glm::vec3& inertia)
{
	this->construct(shape, transform, mass, inertia);
}

void RigidBody::construct(btCollisionShape* shape, const Transform& transform, const float mass, const glm::vec3& inertia)
{
	this->shape = shape;
	this->motion_state = new btDefaultMotionState(transform.toBulletTransform());
	btRigidBody::btRigidBodyConstructionInfo construction_info(mass, this->motion_state, this->shape, btVector3(inertia.x, inertia.y, inertia.z));
	this->body = new btRigidBody(construction_info);
	RigidBody::bind();
}

RigidBody::~RigidBody()
{
	RigidBody::unbind();
    if(this->shape)         delete this->motion_state;
    if(this->motion_state)  delete this->shape;
}

void RigidBody::bind()
{
    PhysicsConfiguration::addRigidBody(this);
}

void RigidBody::unbind()
{
    PhysicsConfiguration::removeRigidBody(this);
}
