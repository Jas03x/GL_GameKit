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
#define DYNAMIC_MESH_MAX_BONE_COUNT 16
#define DYNAMIC_MESH_MAX_NODE_COUNT 16

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
    
    inline const glm::vec3& getScale() const { return this->scale; }
    inline glm::mat4 getMatrix() const { return this->transformation.toMatrix() * glm::scale(this->scale); }
}DynamicMeshInstance;

typedef struct DynamicMesh : public Mesh
{
protected:
    Texture* textures;
    unsigned int texture_count;
    
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
