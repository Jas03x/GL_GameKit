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

#include <map>
#include <vector>

#include "GL.h"
#include "Bone.h"
#include "Math3d.h"
#include "Texture.h"
#include "ColladaLoader.h"

#define DYNAMIC_MESH_MAX_TEXTURE_COUNT 4
#define DYNAMIC_MESH_MAX_NODE_COUNT 16

class DynamicMesh
{
private:
    glm::vec3 scale;
    
protected:
    GLuint vao;
    GLuint vbo;
    
    Texture* textures;
    unsigned int vertex_count;
    unsigned int texture_count;
    
    glm::mat4 inverse_root;
    std::vector<Bone> bones;
    std::map<std::string, Bone*> bone_map;
    
public:
    glm::vec3 position;
    glm::quat rotation;
    
    DynamicMesh(){}
    DynamicMesh(const char* path, const glm::vec3& _scale = glm::vec3(1.0f)) { this->load(path, _scale); }
    void load(const char* path, const glm::vec3& _scale = glm::vec3(1.0f));
    void load(const ColladaLoader& loader, const glm::vec3& _scale = glm::vec3(1.0f));
    void destroy();
    
    inline void bind() const { glBindVertexArray(this->vao); }
    
    inline unsigned int getVertexCount() const { return this->vertex_count; }
    inline unsigned int getTextureCount() const { return this->texture_count; }
    inline const Texture* getTextures() const { return this->textures; }
    
    inline const glm::mat4& getInverseRoot() const { return this->inverse_root; }
    inline const std::vector<Bone>& getBones() const { return this->bones; }
    inline Bone* getBone(const std::string& str) const { return bone_map.at(str); }
    
    inline glm::mat4 getMatrix() const { return glm::translate(this->position) * glm::toMat4(this->rotation) * glm::scale(this->scale); }
};

#endif /* DynamicMesh_h */
