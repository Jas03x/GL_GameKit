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

class MeshCollider : public Collider
{
private:
    btTriangleIndexVertexArray* triangle_iv_array;
    std::vector<int> faces;
    std::vector<glm::vec3> vertices;
    
protected:
    void constructFromStaticMesh(const MeshDescriptor& descriptor, std::vector<int>* face_array = NULL);
    void constructFromDynamicMesh(const MeshDescriptor& descriptor, std::vector<int>* face_array = NULL);
    
public:
    MeshCollider(){}
    MeshCollider(const MeshDescriptor& descriptor, std::vector<int>* face_array = NULL);
    ~MeshCollider();
};

#endif /* MeshCollider_h */
