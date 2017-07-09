//
//  CylinderCollider.h
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef CylinderCollider_h
#define CylinderCollider_h

#include <vector>

#include "Math3d.h"
#include "Collider.h"
#include "RigidBody.h"
#include "ColladaLoader.h"

class CylinderCollider : public RigidBody
{
public:
    CylinderCollider();
    ~CylinderCollider();
    
    static btCylinderShape* getShape(const ColladaLoader& data, const std::vector<int>& faces, const glm::vec3& scale = glm::vec3(1));
};

#endif /* CylinderCollider_h */
