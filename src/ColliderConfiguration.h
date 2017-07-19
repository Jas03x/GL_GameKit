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

class ColliderConfiguration
{
private:
    bool invert_axis;
    glm::vec3 scale;
    
public:
    ColliderConfiguration(const bool _invert_axis = false, const glm::vec3& _scale = glm::vec3(1.0f));
    inline bool axisIsInverted() const { return this->invert_axis; }
    inline const glm::vec3& getScale() const { return this->scale; }
};

#endif /* ColliderConfiguration_h */
