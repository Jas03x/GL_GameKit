//
//  SoftBodyData.h
//  CarDemo
//
//  Created by Jas S on 2017-07-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef SoftBodyData_h
#define SoftBodyData_h

#include <vector>

#include "Math3d.h"
#include "ColladaLoader.h"

// Data structure for caching common softbody data
// This is done to save data when using multiple soft bodies (i.e. to not duplicate vertex, matrix, etc. data)
class SoftBodyData
{
private:
    // collada vertex buffer data:
    std::vector<glm::vec3> vertex_array;
    std::vector<unsigned char> node_indices;
    std::vector<glm::uvec4> bone_indices;
    
    // pointer data:
    const std::vector<Bone>* bones;
    std::vector<glm::mat4> bone_inverse_cache;
    
public:
    SoftBodyData(){}
    SoftBodyData(const ColladaLoader& loader, const std::vector<Bone>& bones, const glm::vec3& scale = glm::vec3(1));
    
    inline const std::vector<glm::vec3>& getVertexArray() const { return this->vertex_array; }
    inline const std::vector<unsigned char>& getNodeIndices() const { return this->node_indices; }
    inline const std::vector<glm::uvec4>& getBoneIndices() const {  return this->bone_indices; }
    
    inline const std::vector<Bone>* getBones() const { return this->bones; }
    inline const std::vector<glm::mat4> getBoneInverseCache() const { return this->bone_inverse_cache; }
};

#endif /* SoftBodyData_h */
