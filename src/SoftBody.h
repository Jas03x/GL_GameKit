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
#include "PhysicsConfiguration.h"

class SoftBody : public Collider
{
protected:
    std::vector<glm::vec3> vertex_array;
    std::vector<int> face_array;
    
    void bind();
    void unbind();
    
public:
    SoftBody(){}
    SoftBody(const std::vector<glm::vec3>& vertices, const std::vector<int>& indices);
    SoftBody(const ColladaLoader& loader, const std::vector<Bone>& bones, const glm::vec3& scale = glm::vec3(1.0f));
    ~SoftBody();
};

#endif /* SoftBody_h */
