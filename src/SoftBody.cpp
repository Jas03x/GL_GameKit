//
//  SoftBody.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "SoftBody.h"

SoftBody::SoftBody(const std::vector<glm::vec3>& vertices, const std::vector<int>& indices, Transform* _transformation) : Collider(_transformation)
{
    this->face_array = indices;
    this->body = btSoftBodyHelpers::CreateFromTriMesh(PhysicsConfiguration::softbody_info, &vertices[0][0], &face_array[0], (unsigned int) this->face_array.size() / 3);
    this->bind();
}

SoftBody::SoftBody(const SoftBodyData& sbdata, const std::vector<int>& face_data, Transform* _transformation, const glm::vec3& scale) : Collider(_transformation)
{
    this->data = &sbdata;
    
    std::vector<glm::mat4> bone_cache = std::vector<glm::mat4>(this->data->getBones()->size());
    for(unsigned int i = 0; i < this->data->getBones()->size(); i++) {
        const Bone& bone = this->data->getBones()[0][i];
        bone_cache.push_back(glm::scale(glm::vec3(scale.x, -scale.y, scale.z)) * bone.bind_pose_matrix * bone.offset_matrix);
    }
    
    this->face_array = face_data;
    this->face_array.shrink_to_fit();
    
    std::vector<glm::vec3> vertex_array;
    vertex_array.reserve(face_data.size());
    for(unsigned int i = 0; i < face_data.size(); i++)
    {
        const glm::vec3& vertex = this->data->getVertexArray()[face_array[i]];
        int index = this->data->getNodeIndices()[face_array[i]];
        vertex_array.push_back(glm::vec3(bone_cache[index] * glm::vec4(vertex, 1)));
    }
    
    this->body = btSoftBodyHelpers::CreateFromTriMesh(PhysicsConfiguration::softbody_info, &vertex_array[0][0], &this->face_array[0], (unsigned int) this->face_array.size() / 3);
    this->bind();
}

SoftBody::~SoftBody()
{
    this->unbind();
}

void SoftBody::bind()
{
    PhysicsConfiguration::addSoftBody(this);
}

void SoftBody::unbind()
{
    PhysicsConfiguration::removeSoftBody(this);
}

// THERE IS A BUG IN THIS FUNCTION AS YOU KNOW
// THIS FUNCTION ONLY ACCOUNTS FOR SINGLE NODE MESHES
// BUT IT DOESNT WORK FOR MULTI NODE MESHES YET
// TODO: ADD FUNCTIONALITY FOR MULTI-BONE INDEX/WEIGHT FACTORS
void SoftBody::getVertexData(std::vector<glm::vec3>& vertex_data)
{
    btSoftBody::tNodeArray& nodes = ((btSoftBody*) body)->m_nodes;
    vertex_data.clear();
    vertex_data.reserve(this->face_array.size());
    
    for(unsigned int i = 0; i < this->face_array.size(); i++) {
        const btVector3& x = nodes[this->face_array[i]].m_x;
        glm::vec3 vec = glm::vec3(x.getX(), x.getY(), x.getZ());
        int index = this->data->getNodeIndices()[this->face_array[i]];
        vertex_data.push_back(glm::vec3(this->data->getBoneInverseCache()[index] * glm::vec4(vec, 1)));
    }
}
