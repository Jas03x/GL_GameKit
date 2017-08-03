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
    glm::vec3 direction; // the direction in units
    int life_time;
    
    Particle(){}
    
    Particle(const glm::vec3& pos, const glm::vec3& dir, int life)
    {
        this->position = pos;
        this->direction = dir;
        this->life_time = life;
    }
    
    void update()
    {
        this->life_time--;
        this->position += direction;
    }
};

#endif /* Particle_hpp */
