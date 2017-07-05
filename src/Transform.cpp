//
//  Transform.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-03.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Transform.h"

Transform::Transform(const glm::vec3& _translation, const glm::quat& _rotation)
{
    this->translation = _translation;
    this->rotation = _rotation;
}
