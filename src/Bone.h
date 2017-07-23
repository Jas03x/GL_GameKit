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

#include "Node.h"
#include "Math3d.h"
#include "Animation.h"
#include "Transform.h"

class Bone
{
public:
    std::string name;
    
    Bone* parent;
    Node* node;
    
    glm::mat4 offset_matrix; // the bone offset matrix
    Transform transform; // a custom transformation
    
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
