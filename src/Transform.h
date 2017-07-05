//
//  Transform.h
//  CarDemo
//
//  Created by Jas S on 2017-07-03.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#include "Math3d.h"

class Transform
{
public:
    glm::vec3 translation;
    glm::quat rotation;
    
    Transform(const glm::vec3& _translation = glm::vec3(0), const glm::quat& _rotation = glm::quat(0, 0, 0, 1));
    
    inline glm::mat4 toMatrix() const { return glm::translate(this->translation) * glm::toMat4(this->rotation); }
};

#endif /* Transform_h */
