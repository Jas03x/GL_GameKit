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
#include "Math3d.h"
#include "Collider.h"
#include "ColladaLoader.h"
#include "SoftBodyData.h"
#include "PhysicsConfiguration.h"

class SoftBody : public Collider
{
protected:
    const SoftBodyData* data;
    std::vector<int> face_array;
    
    void bind();
    void unbind();
    
public:
    SoftBody(){}
    SoftBody(const std::vector<glm::vec3>& vertices, const std::vector<int>& indices, Transform* _transformation);
    // Dynamic mesh constructor:
    SoftBody(const SoftBodyData& sbdata, const std::vector<int>& face_data, Transform* _transformation, const glm::vec3& scale);
    ~SoftBody();
    
    void getVertexData(std::vector<glm::vec3>& vertex_data);
};

#endif /* SoftBody_h */
