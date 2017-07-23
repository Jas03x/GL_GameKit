//
//  CylinderCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CylinderCollider.h"

ColliderData CylinderCollider::getShape(const ColladaLoader& data, const std::vector<int>& faces, const ColliderConfiguration& cc)
{
    std::vector<glm::mat4> bone_cache;
    bone_cache.reserve(data.getBoneNames().size());
    for(unsigned int i = 0; i < data.getBoneNames().size(); i++) {
        const std::string& name = data.getBoneNames()[i];
        const glm::mat4& bindpose = data.getNodeTransforms().at(name);
        const glm::mat4& offset = data.getBoneOffsets().at(name);
        bone_cache.push_back(bindpose * offset);
    }
    const glm::mat4 local_transform = cc.getLocalTransformMatrix() * glm::scale(glm::vec3(cc.getScale()));
    
    // start the vectors at extreme values
    glm::vec3 m = glm::vec3(1000);
    glm::vec3 M = glm::vec3(-1000);
    
    for(unsigned int i = 0; i < faces.size(); i++) {
        const glm::vec3&  vertex = data.getVertices()[faces[i]];
        const glm::uvec4& index  = data.getBoneIndices()[faces[i]];
        const glm::vec4&  weight = data.getBoneWeights()[faces[i]];
        glm::mat4 joint =
            weight.x * bone_cache[index.x] +
            weight.y * bone_cache[index.y] +
            weight.z * bone_cache[index.z] +
            weight.w * bone_cache[index.w];
        
        glm::vec3 vec = glm::vec3(local_transform * joint * glm::vec4(vertex, 1));
        #define MAX_COMPARISON(x, v) if((x) > (v)) (v) = (x);
        #define MIN_COMPARISON(x, v) if((x) < (v)) (v) = (x);
        MAX_COMPARISON(vec.x, M.x);
        MAX_COMPARISON(vec.y, M.y);
        MAX_COMPARISON(vec.z, M.z);
        MIN_COMPARISON(vec.x, m.x);
        MIN_COMPARISON(vec.y, m.y);
        MIN_COMPARISON(vec.z, m.z);
    }
    
    glm::vec3 half_extents = glm::abs(M - m) * 0.5f;
    
    ColliderData cd;
    // TODO: YOU MIGHT NEED TO ADD AN ENUM SYSTEM TO MARK WHICH ORDER THE CYLINDER SHOULD BE CREATED WITH
    // THIS ORDER ISSUE IS THE REASON WHY YOU HAD TO CREATE THIS CYLINDER IN YXZ FORMAT (because the cylinder was rotated!!!)
    cd.shape = new btCylinderShape(btVector3(half_extents.y, half_extents.x, half_extents.z));
    cd.position = m + ((M - m) * 0.5f);
    //cd.position = glm::vec3(cd.position.x, cd.position.z, -cd.position.y);
    //cd.position *= -1;
    //cd.position.z *= -1;
    return cd;
}
