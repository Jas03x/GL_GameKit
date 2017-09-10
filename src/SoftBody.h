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
#include "Mesh.h"
#include "Math3d.h"
#include "Collider.h"
#include "MeshLoader.h"
#include "VectorTree.h"
#include "PhysicsConfiguration.h"
#include "MeshDescriptor.h"

class SoftBody
{
protected:
	btSoftBody* soft_body;
	btDefaultMotionState* motion_state;
	Transform* transform_pointer;
    
	std::vector<int> face_array;
	glm::vec3 scale;

    void bind();
    void unbind();
    
public:
    SoftBody(){}
    // Dynamic mesh constructor:
    SoftBody(MeshDescriptor& descriptor, const std::vector<int>& face_data, const Transform& transform, Transform* ptr = NULL);
    ~SoftBody();
    
    void getVertexData(std::vector<glm::vec3>& vertex_data);
	inline btSoftBody* getSoftBodyPointer() { return this->soft_body; }
	inline const btSoftBody* getSoftBodyPointer() const { return this->soft_body; }
	inline bool hasTransformationPointer() { return transform_pointer != NULL; }
};

class SoftBodyManager
{
private:
	static std::vector<SoftBody*> soft_bodies;
	static btSoftRigidDynamicsWorld* dynamics_world;

public:
	static void Initalize(btSoftRigidDynamicsWorld* _dynamics_world) { dynamics_world = _dynamics_world; }
	static void addSoftBody(SoftBody* soft_body);
	static void removeSoftBody(SoftBody* soft_body);
	static void UpdateBodies();
};

#endif /* SoftBody_h */
