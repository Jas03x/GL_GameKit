//
//  Collider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Collider.h"

Collider::Collider(Transform* _transformation)
{
    this->body = NULL;
    this->transformation = _transformation;
}

Collider::~Collider()
{
    if(this->body) delete this->body;
}

void Collider::bind(){}
void Collider::unbind(){}

void Collider::rotate(const glm::quat& rotation) {
    btTransform transform = this->body->getWorldTransform();
    transform.setRotation(transform.getRotation() * btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
    this->body->setWorldTransform(transform);
}

void Collider::translate(const glm::vec3& translation){
    btTransform transform = this->body->getWorldTransform();
    transform.setOrigin(transform.getOrigin() + btVector3(translation.x, translation.y, translation.z));
    this->body->setWorldTransform(transform);
}

void Collider::transform(const glm::vec3& translation, const glm::quat& rotation)
{
    btTransform transform = this->body->getWorldTransform();
    transform.setOrigin(transform.getOrigin() + btVector3(translation.x, translation.y, translation.z));
    transform.setRotation(transform.getRotation() * btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
    this->body->setWorldTransform(transform);
}
