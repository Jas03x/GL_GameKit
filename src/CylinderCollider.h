//
//  CylinderCollider.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef CylinderCollider_hpp
#define CylinderCollider_hpp

#include <stdio.h>

#include "GLM.h"
#include "World.h"
#include "Collider.h"

class CylinderCollider : public Collider
{
public:
    CylinderCollider() : Collider(glm::vec3(0)) {}
    CylinderCollider(const glm::vec3& length, const glm::vec3& scale, float mass = 0);
    ~CylinderCollider();
};

#endif /* CylinderCollider_hpp */
