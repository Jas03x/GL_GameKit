//
//  Quad.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Quad_hpp
#define Quad_hpp

#include <stdio.h>

#include "GL.h"

namespace Quad
{
    extern const float DATA[12];
    extern GLuint _VAO;
    extern GLuint _VBO;
    
    void init();
    void bind();
    void destroy();
}

#endif /* Quad_hpp */
