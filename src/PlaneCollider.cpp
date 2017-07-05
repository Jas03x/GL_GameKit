//
//  PlaneCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& normal, const float plane_constant, Transform* _transformation, const float mass, const glm::vec3& inertia) : RigidBody(_transformation)
{
    this->shape = new btStaticPlaneShape(btVector3(normal.x, normal.y, normal.z), plane_constant);
    this->motion_state = new btDefaultMotionState(btTransform(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w), btVector3(position.x, position.y, position.z)));
    btRigidBody::btRigidBodyConstructionInfo construction_info(mass, this->motion_state, this->shape, btVector3(inertia.x, inertia.y, inertia.z));
    this->body = new btRigidBody(construction_info);
    RigidBody::bind();
}

PlaneCollider::~PlaneCollider()
{
    RigidBody::unbind();
}
