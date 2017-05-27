//
//  Clock.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Clock_hpp
#define Clock_hpp

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

namespace Clock
{
    extern Uint32 current;
    extern Uint32 last;
    extern float delta;
    
    inline void init() {
        last = SDL_GetTicks();
        current = SDL_GetTicks();
        delta = 0;
    }
    
    inline bool tick() {
        current = SDL_GetTicks();
        delta = (current - last) / 1000.0f; // milliseconds
        if(delta >= 1.0f) {
            last = current;
            return true;
        }
        return false;
    }
    
    inline float getDelta() {
        return delta;
    }
}

class CClock
{
private:
    float delta;
    float ms; // ticks every ms seconds
public:
    CClock();
    CClock(Uint32 milliseconds);
    bool tick();
};

#endif /* Clock_hpp */
