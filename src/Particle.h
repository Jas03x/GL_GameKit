//
//  Particle.hpp
//  RoughRocket
//
//  Created by Jas S on 2017-04-28.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>

#include "Math3d.h"

class Particle
{
public:
    glm::vec3 position;
    
    Particle(){}
    
    Particle(const glm::vec3& pos)
    {
        this->position = pos;
    }
};

#endif /* Particle_hpp */
