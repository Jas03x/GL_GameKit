//
//  CylinderCollider.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CylinderCollider.hpp"

CylinderCollider::CylinderCollider(const glm::vec3& length, const glm::vec3& scale, float mass) : Collider(scale)
{
    this->shape = new btCylinderShape(btVector3(length.x * scale.x, length.y * scale.y, length.z * scale.z));
    this->motion_state = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo constructor = btRigidBody::btRigidBodyConstructionInfo(mass, this->motion_state, this->shape, btVector3(0,0,0));
    this->rigid_body = new btRigidBody(constructor);
    World::addRigidBody(this->rigid_body);
}

CylinderCollider::~CylinderCollider()
{
    World::removeRigidBody(this->rigid_body);
}
