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
    PlaneCollider(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& normal, const float plane_constant, const float mass = 0, const glm::vec3& inertia = glm::vec3(0));
    void destroy();
};

#endif /* PlaneCollider_h */
