//
//  RigidBody.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-02.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "RigidBody.h"

/* RIGID BODY MANAGER */

std::vector<RigidBody*> RigidBodyManager::rigid_bodies;
btDiscreteDynamicsWorld* RigidBodyManager::dynamics_world;

void RigidBodyManager::addRigidBody(RigidBody* rigid_body) {
	std::vector<RigidBody*>::const_iterator it = std::find(rigid_bodies.begin(), rigid_bodies.end(), rigid_body);
	if (it == rigid_bodies.end()) {
		rigid_bodies.push_back(rigid_body);
		dynamics_world->addRigidBody(rigid_body->getRigidBodyPointer());
	}
}

void RigidBodyManager::removeRigidBody(RigidBody* rigid_body) {
	std::vector<RigidBody*>::const_iterator it = std::find(rigid_bodies.begin(), rigid_bodies.end(), rigid_body);
	if (it != rigid_bodies.end()) rigid_bodies.erase(it);
	dynamics_world->removeRigidBody(rigid_body->getRigidBodyPointer());
}

void RigidBodyManager::UpdateBodies() {
	for (unsigned int i = 0; i < rigid_bodies.size(); i++) {
		if (rigid_bodies[i]->hasTransformationPointer()) {
			// printf("Update %i of %i\n", i, (int) colliders.size());
			rigid_bodies[i]->updateTransformationPointer();
		}
	}
}

/* RIGID BODY */

RigidBody::RigidBody(Transform* _transformation)
{
	this->transform_pointer = _transformation;
    this->shape = NULL;
    this->motion_state = NULL;
}

RigidBody::RigidBody(Collider* collider, const Transform& transformation, Transform* t_pointer, const float mass, const glm::vec3& inertia)
{
	this->construct(collider, transformation, t_pointer, mass, inertia);
}

void RigidBody::construct(Collider* collider, const Transform& transformation, Transform* t_pointer, const float mass, const glm::vec3& inertia)
{
	this->shape = collider;
	this->motion_state = new btDefaultMotionState(transformation.toBulletTransform());
	btRigidBody::btRigidBodyConstructionInfo construction_info(mass, this->motion_state, this->shape->getCollisionShape(), btVector3(inertia.x, inertia.y, inertia.z));
	this->rigid_body = new btRigidBody(construction_info);
	this->transform_pointer = t_pointer;
	RigidBody::bind();
}


RigidBody::~RigidBody()
{
	RigidBody::unbind();
	if (this->rigid_body)		delete this->rigid_body;
    if (this->shape)			delete this->shape;
    if (this->motion_state)		delete this->motion_state;
}

void RigidBody::bind()
{
	RigidBodyManager::addRigidBody(this);
}

void RigidBody::unbind()
{
    RigidBodyManager::removeRigidBody(this);
}

void RigidBody::rotate(const glm::quat& rotation) {
	btTransform transform = this->rigid_body->getWorldTransform();
	transform.setRotation(transform.getRotation() * btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	this->rigid_body->setWorldTransform(transform);
}

void RigidBody::translate(const glm::vec3& translation) {
	btTransform transform = this->rigid_body->getWorldTransform();
	transform.setOrigin(transform.getOrigin() + btVector3(translation.x, translation.y, translation.z));
	this->rigid_body->setWorldTransform(transform);
}

void RigidBody::transform(const glm::vec3& translation, const glm::quat& rotation)
{
	btTransform transform = this->rigid_body->getWorldTransform();
	transform.setOrigin(transform.getOrigin() + btVector3(translation.x, translation.y, translation.z));
	transform.setRotation(transform.getRotation() * btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	this->rigid_body->setWorldTransform(transform);
}
