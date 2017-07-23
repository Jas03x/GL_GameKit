//
//  ColliderConfiguration.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-16.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "ColliderConfiguration.h"

ColliderConfiguration::ColliderConfiguration(const Transform& _local_transform, const glm::vec3& _scale)
{
    this->scale = _scale;
    this->local_transform = _local_transform;
}
