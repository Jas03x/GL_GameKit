//
//  Collider.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Collider.hpp"

Collider::Collider(const glm::vec3& _scale)
{
    this->scale = _scale;
}

Collider::~Collider()
{
    if(this->rigid_body != NULL) delete this->rigid_body;
    if(this->motion_state != NULL) delete this->motion_state;
    if(this->shape != NULL) delete this->shape;
}

void Collider::update()
{
}

void Collider::setModelMatrix(const glm::mat4& matrix)
{
    btTransform transform;
    transform.setFromOpenGLMatrix(&matrix[0][0]);
    this->motion_state->setWorldTransform(transform);
    this->rigid_body->setWorldTransform(transform);
}

void Collider::translate(const glm::vec3& translation)
{
    btTransform transform;
    this->motion_state->getWorldTransform(transform);
    transform.setOrigin(
                        btVector3(transform.getOrigin().x() + translation.x,
                                  transform.getOrigin().y() + translation.y,
                                  transform.getOrigin().z() + translation.z));
    this->motion_state->setWorldTransform(transform);
    this->rigid_body->setWorldTransform(transform);
}

void Collider::setTranslation(const glm::vec3& translation)
{
    btTransform transform;
    this->motion_state->getWorldTransform(transform);
    transform.setOrigin(btVector3(translation.x, translation.y, translation.z));
    this->motion_state->setWorldTransform(transform);
    this->rigid_body->setWorldTransform(transform);
}

void Collider::rotate(const glm::vec3& rotation)
{
    btTransform transform;
    this->motion_state->getWorldTransform(transform);
    transform.setRotation(transform.getRotation() * btQuaternion(rotation.y, rotation.x, rotation.z));
    this->motion_state->setWorldTransform(transform);
    this->rigid_body->setWorldTransform(transform);
}

void Collider::setRotation(const glm::vec3& rotation)
{
    btTransform transform;
    this->motion_state->getWorldTransform(transform);
    transform.setRotation(btQuaternion(rotation.y, rotation.x, rotation.z));
    this->motion_state->setWorldTransform(transform);
    this->rigid_body->setWorldTransform(transform);
}
