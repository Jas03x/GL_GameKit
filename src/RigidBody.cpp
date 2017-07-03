//
//  RigidBody.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-02.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "RigidBody.h"

RigidBody::RigidBody()
{
    this->shape = NULL;
    this->motion_state = NULL;
}

RigidBody::~RigidBody()
{
    if(this->shape)         delete this->motion_state;
    if(this->motion_state)  delete this->shape;
}

void RigidBody::bind()
{
    PhysicsConfiguration::addRigidBody((btRigidBody*) this->body);
}

void RigidBody::unbind()
{
    PhysicsConfiguration::removeRigidBody((btRigidBody*) this->body);
}
