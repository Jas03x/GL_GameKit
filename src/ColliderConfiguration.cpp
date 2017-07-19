//
//  ColliderConfiguration.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-16.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "ColliderConfiguration.h"

ColliderConfiguration::ColliderConfiguration(const bool _invert_axis, const glm::vec3& _scale)
{
    this->scale = _scale;
    this->invert_axis = _invert_axis;
}
