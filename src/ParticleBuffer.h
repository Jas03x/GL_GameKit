//
//  ParticleBuffer.hpp
//  RoughRocket
//
//  Created by Jas S on 2017-04-28.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef ParticleBuffer_hpp
#define ParticleBuffer_hpp

#include <stdio.h>
#include <array>

#include "Quad.h"
#include "Texture.h"
#include "Particle.h"

// TODO:
// Change constructors so that you can either use a quad or a mesh
// The VBO will simply be created based off the quad or mesh
// So you only need to 2 types of buffers: Textured and solid colored

// base particle class
class TParticleBuffer
{
protected:
    GLuint VAO;
    GLuint VBO;
    Texture texture;
    glm::vec2 render_scale; // the size of the objects which are rendered
    glm::vec2 sprite_size;  // the subdivision lengths of the texture (in pixels)
    unsigned int instance_count; // the number of valid textures
    
    void genVertexArrays(int max_particles);
    
public:
    TParticleBuffer(){}
    
    inline void bindVAO() const { glBindVertexArray(this->VAO); }
    inline const Texture& getTexture() const { return this->texture; }
    inline const glm::vec2& getRenderScale() const { return this->render_scale; }
    inline const glm::vec2& getSpriteSize() const { return this->sprite_size; }
    inline unsigned int getInstanceCount() const { return this->instance_count; }
    
    void destroy();
};


class CParticleBuffer
{
    
};

#endif /* ParticleBuffer_hpp */
