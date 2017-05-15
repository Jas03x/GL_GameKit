//
//  CharacterRenderer.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef CharacterRenderer_hpp
#define CharacterRenderer_hpp

#include <stdio.h>

#include "Camera.h"
#include "Shader.h"
#include "Character.h"

class CharacterRenderer : public Shader
{
private:
    GLuint texture_id;
    GLuint camera_matrix;
    
public:
    CharacterRenderer(){}
    void load();
    void render(const Character& character);
    void destroy();
};

#endif /* CharacterRenderer_hpp */
