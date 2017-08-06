//
//  MeshCollider.h
//  Automata
//
//  Created by Jas S on 2017-08-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef MeshCollider_h
#define MeshCollider_h

#include <stdio.h>

#include "Mesh.h"
#include "RigidBody.h"
#include "MeshLoader.h"
#include "VectorTree.h"
#include "MeshDescriptor.h"
#include "PhysicsConfiguration.h"

class MeshCollider : public RigidBody
{
private:
    btTriangleIndexVertexArray* triangle_iv_array;
    std::vector<int> faces;
    std::vector<glm::vec3> vertices;
    
protected:
    void constructFromStaticMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia);
    void constructFromDynamicMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia);
    
public:
    MeshCollider(){}
    MeshCollider(const MeshDescriptor& descriptor, const float mass = 0, const glm::vec3& inertia = glm::vec3(0));
    ~MeshCollider();
};

#endif /* MeshCollider_h */
