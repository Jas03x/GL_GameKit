//
//  SoftBody.h
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef SoftBody_h
#define SoftBody_h

#include <vector>
#include <BulletSoftBody/btSoftBodyHelpers.h>

#include "Bone.h"
#include "Mesh.h"
#include "Math3d.h"
#include "Collider.h"
#include "ColladaLoader.h"
#include "PhysicsConfiguration.h"
#include "ColliderConfiguration.h"

class SoftBody : public Collider
{
protected:
    std::vector<int> face_array;
    glm::vec3 scale;
    
    void bind();
    void unbind();
    
public:
    SoftBody(){}
    // Dynamic mesh constructor:
    SoftBody(const ColliderConfiguration& collider_configuration, ColladaLoader& loader, const std::vector<int>& face_data, const Transform& transform, Transform* ptr = NULL);
    ~SoftBody();
    
    void getVertexData(std::vector<glm::vec3>& vertex_data);
};

#endif /* SoftBody_h */
