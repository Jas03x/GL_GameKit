//
//  Transform.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-03.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Transform.h"

Transform::Transform(const glm::vec3& _translation, const glm::vec3& _rotation)
{
    this->translation = _translation;
    this->rotation = glm::quat(_rotation);
}

Transform::Transform(const glm::vec3& _translation, const glm::quat& _rotation)
{
    this->translation = _translation;
    this->rotation = glm::quat(_rotation.w, _rotation.x, _rotation.y, _rotation.z);
}
