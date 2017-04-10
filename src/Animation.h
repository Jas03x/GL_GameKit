//
//  Animation.h
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Animation_h
#define Animation_h

#include <vector>

#include "GLM.h"
#include "Clock.h"

class Animation
{
public:
    std::vector<glm::vec3> translations;
    std::vector<glm::vec4> rotations;
    std::vector<glm::vec3> scales;
    
    Animation(){}
    Animation(const std::vector<glm::vec3>& _translations, const std::vector<glm::vec4>& _rotations, const std::vector<glm::vec3>& _scales) {
        this->translations = _translations;
        this->rotations = _rotations;
        this->scales = _scales;
    }
    
    inline const glm::mat4 interpolate(unsigned int frame) const
    {
        unsigned int next_frame = frame + 1;
        if(next_frame >= this->translations.size()) next_frame = 0;
        
        glm::quat start = glm::quat(this->rotations.at(frame).w, this->rotations.at(frame).x, this->rotations.at(frame).y, this->rotations.at(frame).z);
        glm::quat end = glm::quat(this->rotations.at(next_frame).w, this->rotations.at(next_frame).x, this->rotations.at(next_frame).y, this->rotations.at(next_frame).z);
        
        glm::quat quaternion = glm::slerp(start, end, std::min(Clock::getDelta(), 1.0f));
        glm::vec3 difference = this->translations.at(next_frame) - this->translations.at(frame);
        glm::vec3 translation = this->translations.at(frame) + difference * std::min(Clock::getDelta(), 1.0f);
        
        return glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(quaternion);
    }
};

#endif /* Animation_h */
