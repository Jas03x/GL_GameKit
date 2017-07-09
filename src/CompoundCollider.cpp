//
//  CompoundCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CompoundCollider.h"

CompoundCollider::CompoundCollider(const Transform& transform, Transform* ptr, const float mass, const glm::vec3& inertia) : RigidBody(ptr)
{
    this->shape = new btCompoundShape();
    this->motion_state = new btDefaultMotionState(transform.toBulletTransform());
    btRigidBody::btRigidBodyConstructionInfo construction_info(mass, this->motion_state, this->shape, btVector3(inertia.x, inertia.y, inertia.z));
    this->body = new btRigidBody(construction_info);
    RigidBody::bind();
}

CompoundCollider::~CompoundCollider()
{
    for(unsigned int i = 0; i < this->child_shapes.size(); i++) delete this->child_shapes[i];
    RigidBody::unbind();
}

void CompoundCollider::bind()   { PhysicsConfiguration::addRigidBody(this); }
void CompoundCollider::unbind() { PhysicsConfiguration::removeRigidBody(this); }

void CompoundCollider::addCollisionShape(const Transform& local_transform, btCollisionShape* shape)
{
    this->child_shapes.push_back(shape);
    ((btCompoundShape*) this->shape)->addChildShape(local_transform.toBulletTransform(), shape);
}
