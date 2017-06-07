//
//  StaticMesh.h
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef StaticMesh_h
#define StaticMesh_h

#include <stdio.h>

#include <vector>

#include "GL.h"
#include "Math3d.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class StaticMesh
{
private:
    GLuint vao;
    GLuint vbo;
    Texture texture;
    unsigned int vertex_count;
    
public:
    glm::mat4 model_matrix;
    
	StaticMesh(){}
	StaticMesh(GLuint _vao, GLuint _vbo, const char* _texture, unsigned int _vertex_count);
    
    void load(const char* source, const char* texture);
    inline void bind() const { glBindVertexArray(this->vao); }
    inline const Texture& getTexture() const { return this->texture; }
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    void destroy();
};

#endif /* StaticMesh_h */
