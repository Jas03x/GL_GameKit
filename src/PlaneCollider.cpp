//
//  PlaneCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(Transform transform, const glm::vec3& normal, const float plane_constant, const float mass, const glm::vec3& inertia)
{
	this->construct(new btStaticPlaneShape(btVector3(normal.x, normal.y, normal.z), plane_constant), transform, mass, inertia);
}

PlaneCollider::~PlaneCollider()
{
    RigidBody::unbind();
}
