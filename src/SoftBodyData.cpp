//
//  SoftBodyData.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "SoftBodyData.h"

SoftBodyData::SoftBodyData(const ColladaLoader& loader, const std::vector<glm::mat4>& nodes, const std::vector<Bone>& bones, const glm::vec3& scale)
{
    this->vertex_array = loader.getVertices();
    this->node_indices = loader.getNodeIndices();
    this->bone_indices = loader.getBoneIndices();
    this->bone_weights = loader.getBoneWeights();
    
    this->nodes = &nodes;
    this->bones = &bones;
    
    this->inverse_matrix = loader.getInverseRoot();
    this->bone_inverse_cache.reserve(bones.size());
    for(int i = 0; i < bones.size(); i++) {
        glm::mat4 matrix = glm::scale(glm::vec3(scale.x, -scale.y, scale.z)) * bones[i].bind_pose_matrix * bones[i].offset_matrix;
        this->bone_inverse_cache.push_back(glm::inverse(matrix));
    }
}
