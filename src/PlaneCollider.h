//
//  PlaneCollider.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef PlaneCollider_h
#define PlaneCollider_h

#include "Math3d.h"
#include "Collider.h"
#include "RigidBody.h"

class PlaneCollider : public RigidBody
{
private:
    
public:
    PlaneCollider(Transform transform, const glm::vec3& normal = glm::vec3(0, 1, 0), const float plane_constant = 0, const float mass = 0, const glm::vec3& inertia = glm::vec3(0));
    ~PlaneCollider();
};

#endif /* PlaneCollider_h */
