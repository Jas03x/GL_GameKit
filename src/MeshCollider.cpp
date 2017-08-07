//
//  MeshCollider.cpp
//  Automata
//
//  Created by Jas S on 2017-08-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "MeshCollider.h"

MeshCollider::MeshCollider(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia)
{
    if(descriptor.getMeshLoader().getBoneNames().size() > 0)
        this->constructFromDynamicMesh(descriptor, mass, inertia);
    else this->constructFromStaticMesh(descriptor, mass, inertia);
}

void MeshCollider::constructFromStaticMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia)
{
    /*
     void MeshLoader::getStaticVertexArray(std::vector<glm::vec3>& source) const
     {
        source.clear();
        source.reserve(this->faces.size());
        for(unsigned int i = 0; i < this->faces.size(); i++)
        source.push_back(glm::vec3(this->node_transforms[this->node_indices[this->faces[i]]] * glm::vec4(this->vertices[this->faces[i]], 1)));
     }
     */

    const MeshLoader& data = descriptor.getMeshLoader();
    this->faces.reserve(descriptor.getMeshLoader().getFaces().size());
    VectorTree vertex_tree;
    const glm::mat4 OFFSET = descriptor.getTransform().toMatrix() * glm::scale(descriptor.getScale());
    for(unsigned int i = 0; i < data.getFaces().size(); i++) {
        unsigned int face = data.getFaces()[i];
        glm::vec3 vertex = glm::vec3(OFFSET * data.getNodeTransforms()[data.getNodeIndices()[face]] * glm::vec4(data.getVertices()[face], 1));
        this->faces.push_back(vertex_tree.insert(vertex));
    }
    vertex_tree.toArray(this->vertices);

	this->triangle_iv_array = new btTriangleIndexVertexArray((int) faces.size() / 3, &faces[0], sizeof(int) * 3, (unsigned int) vertices.size(), &vertices[0][0], sizeof(glm::vec3));
	this->shape = new btBvhTriangleMeshShape(triangle_iv_array, true);
    
    this->motion_state = new btDefaultMotionState(descriptor.getTransform().toBulletTransform());
    btRigidBody::btRigidBodyConstructionInfo construction_info(mass, this->motion_state, this->shape, btVector3(inertia.x, inertia.y, inertia.z));
    this->body = new btRigidBody(construction_info);
    RigidBody::bind();
}

void MeshCollider::constructFromDynamicMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia)
{
    // TODO: IMPLEMENT!!!
    // NOTE: VERY SIMILAR PROCESS TO THE SOFTBODY CONSTRUCTION!!!
    printf("Error: Mesh collider construction from dynamic mesh not yet implemented!\n");
    throw -1;
}

MeshCollider::~MeshCollider()
{
    RigidBody::unbind();
    if(this->triangle_iv_array) delete this->triangle_iv_array;
}
