//
//  Quad.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Quad.hpp"

const float QUAD[12] =
{
    // top triangle
    1.0f,  1.0f, // top right
    -1.0f,  1.0f, // top left
    -1.0f, -1.0f, // bottom left
    // bottom triangle:
    1.0f,  1.0f, // top right
    -1.0f, -1.0f, // bottom left
    1.0f, -1.0f  // bottom right
};

