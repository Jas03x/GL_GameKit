//
//  CompoundCollider.h
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef CompoundCollider_h
#define CompoundCollider_h

#include <vector>

#include "Mesh.h"
#include "Math3d.h"
#include "Collider.h"
#include "RigidBody.h"
#include "PhysicsConfiguration.h"
#include "ColliderConfiguration.h"

class CompoundCollider : public RigidBody
{
private:
    std::vector<btCollisionShape*> child_shapes;
    
    void bind();
    void unbind();
    
public:
    CompoundCollider(const ColliderConfiguration& collider_configuration, const Transform& transform, Transform* ptr = NULL, const float mass = 0, const glm::vec3& inertia = glm::vec3(0));
    ~CompoundCollider();
    
    void addCollisionShape(const Transform& local_transform, btCollisionShape* shape);
};

#endif /* CompoundCollider_h */
