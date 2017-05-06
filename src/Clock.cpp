//
//  Clock.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Clock.h"

Uint32 Clock::last;
Uint32 Clock::current;
float Clock::delta;

CClock::CClock()
{
    this->ms = 0;
    this->delta = 0;
}

CClock::CClock(Uint32 milliseconds)
{
    this->ms = milliseconds/1000.0f;
    this->delta = 0;
}

bool CClock::tick()
{
    this->delta += Clock::delta;
    if(this->delta >= this->ms)
    {
        this->delta = 0;
        return true;
    }
    return false;
}
