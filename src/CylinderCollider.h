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
#include "ColliderConfiguration.h"

typedef struct ColliderData
{
    btCollisionShape* shape;
    glm::vec3 position;
}ColliderData;

class CylinderCollider : public RigidBody
{
public:
    CylinderCollider();
    ~CylinderCollider();
    
    static ColliderData getShape(const ColladaLoader& data, const std::vector<int>& faces, const ColliderConfiguration& cc);
};

#endif /* CylinderCollider_h */
