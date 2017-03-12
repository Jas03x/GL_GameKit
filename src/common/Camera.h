//
//  Camera.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "GLM.h"

// the camera designed to stay behind the player
namespace Camera
{
    extern glm::mat4 model, view, projection;
    extern glm::mat4 mv, mvp;
    
    void init(float width, float height);
    
    inline void update() {
        mv = view * model;
        mvp = projection * mv;
    }
}


#endif /* Camera_hpp */
