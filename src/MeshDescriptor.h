//
//  MeshDescriptor.h
//
//  Created by Jas S on 2017-07-29.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef MeshDescriptor_h
#define MeshDescriptor_h

#include <stdio.h>

#include "GL.h"
#include "MeshLoader.h"

class MeshDescriptor
{
private:
    MeshLoader loader;
    glm::vec3 scale;
    GLenum draw_mode;
    
public:
    MeshDescriptor(const char* path, unsigned int parameters, const glm::vec3& _scale = glm::vec3(1.0f), const GLenum _draw_mode = GL_STATIC_DRAW) : loader(path, parameters) {
        this->scale = _scale;
        this->draw_mode = _draw_mode;
    }
    
    MeshDescriptor(const char* path, const glm::vec3& _scale = glm::vec3(1.0f), const GLenum _draw_mode = GL_STATIC_DRAW) : loader(path) {
        this->scale = _scale;
        this->draw_mode = _draw_mode;
    }
    
    inline GLenum getDrawMode() const { return this->draw_mode; }
    inline const glm::vec3& getScale() const { return this->scale; }
    
    inline MeshLoader& getMeshLoader() { return this->loader; }
    inline const MeshLoader& getMeshLoader() const { return this->loader; }
};

#endif /* MeshDescriptor_h */
