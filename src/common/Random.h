//
//  Random.h
//  Bad_Ninja
//
//  Created by Jas S on 2016-12-27.
//  Copyright © 2016 Jas S. All rights reserved.
//

#ifndef Random_h
#define Random_h

#include <time.h>
#include <stdlib.h>

namespace Random
{
    inline void init() {
        srand((unsigned int) time(NULL));
    }
    
    inline int genInt(int max) {
        return rand() % max;
    }
    
    inline bool genBool() {
        return rand() % 2 == 0;
    }

}

#endif /* Random_h */
