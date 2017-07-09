//
//  CylinderCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CylinderCollider.h"

btCylinderShape* CylinderCollider::getShape(const ColladaLoader& data, const std::vector<int>& faces, const glm::vec3& scale)
{
    std::vector<glm::mat4> bone_cache;
    bone_cache.reserve(data.getBoneNames().size());
    for(unsigned int i = 0; i < data.getBoneNames().size(); i++) {
        const std::string& name = data.getBoneNames()[i];
        const glm::mat4& bindpose = data.getNodeTransforms().at(name);
        const glm::mat4& offset = data.getBoneOffsets().at(name);
        bone_cache.push_back(bindpose * offset);
    }
    const glm::mat4 scale_matrix = glm::scale(glm::vec3(scale.x, -scale.y, scale.z));
    
    glm::vec3 min = glm::vec3(0);
    glm::vec3 max = glm::vec3(0);
    
    for(unsigned int i = 0; i < faces.size(); i++) {
        const glm::vec3&  vertex = data.getVertices()[faces[i]];
        const glm::uvec4& index  = data.getBoneIndices()[faces[i]];
        const glm::vec4&  weight = data.getBoneWeights()[faces[i]];
        glm::mat4 joint =
            weight.x * bone_cache[index.x] +
            weight.y * bone_cache[index.y] +
            weight.z * bone_cache[index.z] +
            weight.w * bone_cache[index.w];
        
        glm::vec3 vec = glm::vec3(scale_matrix * joint * glm::vec4(vertex, 1));
        #define MAX_COMPARISON(x, v) if(x > v) v = x;
        #define MIN_COMPARISON(x, v) if(x < v) v = x;
        MAX_COMPARISON(vec.x, max.x);
        MAX_COMPARISON(vec.y, max.y);
        MAX_COMPARISON(vec.z, max.z);
        MIN_COMPARISON(vec.x, min.x);
        MIN_COMPARISON(vec.y, min.y);
        MIN_COMPARISON(vec.z, min.z);
    }
    
    glm::vec3 half_extents = (max - min) * 0.5f;
    return new btCylinderShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
}
