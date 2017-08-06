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
#include "Node.h"
#include "Mesh.h"
#include "Math3d.h"
#include "Texture.h"
#include "Transform.h"
#include "MeshLoader.h"
#include "MeshDescriptor.h"

#define DYNAMIC_MESH_MAX_TEXTURE_COUNT 4
#define DYNAMIC_MESH_MAX_BONE_COUNT 20
#define DYNAMIC_MESH_MAX_NODE_COUNT 20

typedef struct DynamicMeshInstance
{
private:
    glm::vec3 scale;
    
public:
    Transform transformation;
    std::vector<Bone> bones;
    std::vector<Node> nodes;
    std::map<std::string, unsigned int> bone_map;
    std::map<std::string, unsigned int> node_map;
    
    DynamicMeshInstance(){}
    DynamicMeshInstance(const glm::vec3& _scale) : scale(_scale) {}
    
    DynamicMeshInstance(const DynamicMeshInstance& other) {
        this->scale = other.scale;
        this->transformation = other.transformation;
        this->nodes = other.nodes;
        this->bone_map = other.bone_map;
        this->node_map = other.node_map;
        
        this->bones.reserve(other.bones.size());
        for(unsigned int i = 0; i < other.bones.size(); i++) {
            Bone bone = Bone(other.bones[i].name);
            bone.parent = NULL;
            bone.node = &this->nodes[this->node_map.at(other.bones[i].node->name)];
            bone.offset_matrix = other.bones[i].offset_matrix;
            bone.animation = other.bones[i].animation;
            this->bones.push_back(bone);
        }
        
        for(unsigned int i = 0; i < other.bones.size(); i++) {
            const Bone& bone = other.bones[i];
            if(bone.parent)
                this->bones[i].parent = &this->bones[this->bone_map.at(bone.parent->name)];
        }
    }
    
    inline const glm::vec3& getScale() const { return this->scale; }
    inline glm::mat4 getMatrix() const { return this->transformation.toMatrix() * glm::scale(this->scale); }
}DynamicMeshInstance;

typedef struct DynamicMesh : public Mesh
{
protected:
    Texture* textures;
    unsigned int texture_count;
    std::vector<float> materials;
    
    glm::mat4 inverse_root;
    
    DynamicMeshInstance default_instance;
    
    void generateNodes(const MeshLoader& loader);
    void construct(const MeshLoader& loader, const glm::vec3& _scale = glm::vec3(1.0f), GLenum draw_mode = GL_STATIC_DRAW);
    
public:
    DynamicMesh(){}
    void destroy();
    
    DynamicMesh(const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getDrawMode()); }
    void operator = (const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getDrawMode()); }
    
    inline const Texture* getTextures() const { return this->textures; }
    inline unsigned int getTextureCount() const { return this->texture_count; }
    
    inline const glm::mat4& getInverseRoot() const { return this->inverse_root; }
    
    inline DynamicMeshInstance& getDefaultInstance() { return this->default_instance; }
    inline const DynamicMeshInstance& getDefaultInstance() const { return this->default_instance; }
}DynamicMesh;

#endif /* DynamicMesh_h */
