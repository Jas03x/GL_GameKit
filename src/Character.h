//
//  Character.hpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>

#include <vector>

#include "GL.h"
#include "GLM.h"
#include "Texture.h"
#include "ColladaLoader.h"

class Character
{
protected:
    GLuint vao;
    GLuint vbo;
    Texture texture;
    unsigned int vertex_count;
    
    void load(const char* source, const char* texture);
    void destroy();
    
public:
    glm::mat4 model_matrix;
    
    Character(){}
    
    inline void bind() const { glBindVertexArray(this->vao); }
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    inline const Texture& getTexture() const { return this->texture; }
};

#endif /* Character_hpp */
