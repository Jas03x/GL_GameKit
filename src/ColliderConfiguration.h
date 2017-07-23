//
//  ColliderConfiguration.h
//  CarDemo
//
//  Created by Jas S on 2017-07-16.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef ColliderConfiguration_h
#define ColliderConfiguration_h

#include "Math3d.h"
#include "Transform.h"

class ColliderConfiguration
{
private:
    Transform local_transform;
    glm::vec3 scale;
    
public:
    ColliderConfiguration(const Transform& _local_transform = Transform(), const glm::vec3& _scale = glm::vec3(1.0f));
    inline const glm::vec3& getScale() const { return this->scale; }
    inline glm::mat4 getLocalTransformMatrix() const { return this->local_transform.toMatrix(); }
};

#endif /* ColliderConfiguration_h */
