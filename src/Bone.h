//
//  Bone.h
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Bone_h
#define Bone_h

#include <string>
#include <vector>

#include "GLM.h"
#include "Animation.h"

class Bone
{
public:
    Bone* parent;
    std::string name;
    glm::mat4 offset_matrix; // the bone offset matrix
    glm::mat4 bind_pose_matrix; // the bind pose matrix from the node heirchy
    glm::mat4 transformation_matrix; // a custom transformation
    Animation animation; // the animation for this bone
    
    Bone(){}
    Bone(std::string _name){ this->name = _name; }
    
    inline glm::mat4 interpolate(unsigned int frame) const
    {
        glm::mat4 result = glm::mat4(1.0f);
        const Bone* p = this;
        
        while(p != NULL)
        {
            result = p->animation.interpolate(frame) * result;
            p = p->parent;
        }
        
        return result;
    }
};

#endif /* Bone_h */
