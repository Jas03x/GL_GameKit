//
//  SoftBody.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-01.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "SoftBody.h"

SoftBody::SoftBody(const std::vector<glm::vec3>& vertices, const std::vector<int>& indices)
{
    this->vertex_array = vertices;
    this->face_array = indices;
    this->body = btSoftBodyHelpers::CreateFromTriMesh(PhysicsConfiguration::softbody_info, &vertex_array[0][0], &face_array[0], (unsigned int) this->face_array.size() / 3);
    this->bind();
}

SoftBody::SoftBody(const ColladaLoader& loader, const std::vector<Bone>& bones, const glm::vec3& scale)
{
    std::vector<glm::mat4> bone_cache = std::vector<glm::mat4>(bones.size());
    for(unsigned int i = 0; i < bones.size(); i++)
        bone_cache[i] = glm::scale(glm::vec3(scale.x, -scale.y, scale.z)) * bones[i].bind_pose_matrix;
    
    this->face_array = loader.getFaces();
    face_array.shrink_to_fit();
    this->vertex_array.reserve(loader.getFaces().size());
    for(unsigned int i = 0; i < loader.getFaces().size(); i++)
    {
        const glm::vec3& vertex = loader.getVertices()[face_array[i]];
        int index = loader.getNodeIndices()[face_array[i]];
        this->vertex_array.push_back(glm::vec3(bone_cache[index] * glm::vec4(vertex, 1)));
    }
    
    this->body = btSoftBodyHelpers::CreateFromTriMesh(PhysicsConfiguration::softbody_info, &this->vertex_array[0][0], &this->face_array[0], (unsigned int) this->face_array.size() / 3);
    this->bind();
}

SoftBody::~SoftBody()
{
    this->unbind();
}

void SoftBody::bind()
{
    PhysicsConfiguration::addSoftBody((btSoftBody*) this->body);
}

void SoftBody::unbind()
{
    PhysicsConfiguration::removeSoftBody((btSoftBody*) this->body);
}
