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
#include "Mesh.h"
#include "Math3d.h"
#include "Texture.h"
#include "Transform.h"
#include "MeshLoader.h"
#include "MeshDescriptor.h"

#define STATIC_MESH_MAX_TEXTURE_COUNT 1

typedef struct StaticMeshInstance
{
private:
    glm::vec3 scale;
    
public:
    Transform transform;
    
    StaticMeshInstance(){}
    StaticMeshInstance(const glm::vec3& _scale) : scale(_scale) {}
    
    inline glm::mat4 getMatrix() const { return this->transform.toMatrix() * glm::scale(this->scale); }
    inline const glm::vec3& getScale() const { return this->scale; }
}StaticMeshInstance;

typedef struct StaticMesh : public Mesh
{
private:
    Texture texture;
    
protected:
    StaticMeshInstance default_instance;
    std::vector<float> materials;
    
    void construct(const MeshLoader& loader, const glm::vec3& _scale = glm::vec3(1.0f), const Transform& transform = Transform(), const GLenum draw_mode = GL_STATIC_DRAW);
    
public:
	StaticMesh(){}
    void destroy();
    
    StaticMesh(const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getTransform(), descriptor.getDrawMode()); }
    void operator = (const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getTransform(), descriptor.getDrawMode()); }
    
    inline void setTexture(const Texture& other){ this->texture = other; }
    inline const Texture& getTexture() const { return this->texture; }
    inline const std::vector<float>& getMaterials() const { return this->materials; }
    
    inline StaticMeshInstance& getDefaultInstance() { return this->default_instance; }
    inline const StaticMeshInstance& getDefaultInstance() const { return this->default_instance; }
}StaticMesh;

#endif /* StaticMesh_h */
