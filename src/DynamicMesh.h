//
//  DynamicMesh.h
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DynamicMesh_h
#define DynamicMesh_h

#include <stdio.h>

#include <vector>

#include "GL.h"
#include "Math3d.h"
#include "Texture.h"
#include "ColladaLoader.h"

#define DYNAMIC_MESH_MAX_TEXTURE_COUNT 4

// TODO: IMPLEMENT BONES
class DynamicMesh
{
protected:
    GLuint vao;
    GLuint vbo;
    
    Texture* textures;
    unsigned int vertex_count;
    unsigned int texture_count;
    
public:
    glm::mat4 model_matrix;
    
    DynamicMesh(){}
    DynamicMesh(const char* path, const char* file_name){ this->load(path, file_name); }
    
    void load(const char* path, const char* file_name);
    inline void bind() const { glBindVertexArray(this->vao); }
    void destroy();
    
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    inline unsigned int getTextureCount() const { return this->texture_count; }
    inline const Texture* getTextures() const { return this->textures; }
};

#endif /* DynamicMesh_h */
