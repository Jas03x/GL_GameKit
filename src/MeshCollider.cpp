//
//  MeshCollider.cpp
//  Automata
//
//  Created by Jas S on 2017-08-05.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "MeshCollider.h"

MeshCollider::MeshCollider(const MeshDescriptor& descriptor, std::vector<int>* face_array)
{
    if(descriptor.getMeshLoader().getBoneNames().size() > 0)
        this->constructFromDynamicMesh(descriptor, face_array);
    else this->constructFromStaticMesh(descriptor, face_array);
}

void MeshCollider::constructFromStaticMesh(const MeshDescriptor& descriptor, std::vector<int>* face_array)
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
    VectorTree vertex_tree;
    //const glm::mat4 local_transform = descriptor.getTransform().toMatrix() * glm::scale(descriptor.getScale());
	const glm::mat4 local_transform = glm::scale(descriptor.getScale());
	//const std::vector<int>& face_data = face_array ? *face_array : data.getFaces();
	const std::vector<int>& face_data = data.getFaces();
	this->faces.reserve(face_data.size());
    for(unsigned int i = 0; i < face_data.size(); i++) {
        const unsigned int face = face_data[i];
        glm::vec3 vertex = glm::vec3(local_transform * data.getNodeTransforms()[data.getNodeIndices()[face]] * glm::vec4(data.getVertices()[face], 1));
        this->faces.push_back(vertex_tree.insert(vertex));
    }
    vertex_tree.toArray(this->vertices);

	this->triangle_iv_array = new btTriangleIndexVertexArray((int) faces.size() / 3, &faces[0], sizeof(int) * 3, (unsigned int) vertices.size(), &vertices[0][0], sizeof(glm::vec3));
	this->shape = new btBvhTriangleMeshShape(triangle_iv_array, true);
}

void MeshCollider::constructFromDynamicMesh(const MeshDescriptor& descriptor, std::vector<int>* face_array)
{
    // TODO: IMPLEMENT!!!
    // NOTE: VERY SIMILAR PROCESS TO THE SOFTBODY CONSTRUCTION!!!
    printf("Error: Mesh collider construction from dynamic mesh not yet implemented!\n");
    throw -1;
}

MeshCollider::~MeshCollider()
{
    //RigidBody::unbind();
    if(this->triangle_iv_array) delete this->triangle_iv_array;
}
