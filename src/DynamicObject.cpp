//
//  DynamicObject.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
    this->collider = NULL;
}

void DynamicObject::destroy()
{
    DynamicMesh::destroy();
    if(this->collider) delete this->collider;
}

void DynamicObject::update_transform()
{
    btTransform transform = this->collider->getCollisionObject()->getWorldTransform();
    const btVector3& origin = transform.getOrigin();
    const btQuaternion& rot = transform.getRotation();
    this->position = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
    this->rotation = glm::quat(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
}
