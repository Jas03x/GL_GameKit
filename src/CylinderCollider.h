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
#include "MeshLoader.h"
#include "ColliderData.h"
#include "MeshDescriptor.h"

class CylinderCollider : public RigidBody
{
public:
    CylinderCollider();
    ~CylinderCollider();
    
    static ColliderData getShape(const MeshDescriptor& descriptor, const std::vector<int>& faces);
};

#endif /* CylinderCollider_h */
