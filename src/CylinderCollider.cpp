//
//  CylinderCollider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "CylinderCollider.h"

CylinderCollider::CylinderCollider(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia)
	: CylinderCollider(descriptor, descriptor.getMeshLoader().getFaces(), mass, inertia) {}

CylinderCollider::CylinderCollider(const MeshDescriptor& descriptor, const std::vector<int>& faces, const float mass, const glm::vec3& inertia)
{
	const MeshLoader& loader = descriptor.getMeshLoader();
	this->construct(this->getShape(descriptor, &faces).shape, descriptor.getTransform(), mass, inertia);
}

CylinderCollider::~CylinderCollider()
{
	RigidBody::unbind();
}

ColliderData CylinderCollider::getShape(const MeshDescriptor& descriptor, const std::vector<int>* faces)
{
	std::pair<glm::vec3, glm::vec3> bounds = ColliderUtilities::calculate_bounds(descriptor, faces);
    
	ColliderData cd;
    glm::vec3 half_extents = glm::abs(bounds.second * bounds.first) * 0.5f;
    
    // TODO: YOU MIGHT NEED TO ADD AN ENUM SYSTEM TO MARK WHICH ORDER THE CYLINDER SHOULD BE CREATED WITH
    // THIS ORDER ISSUE IS THE REASON WHY YOU HAD TO CREATE THIS CYLINDER IN YXZ FORMAT (because the cylinder was rotated!!!)
    cd.shape = new btCylinderShape(btVector3(half_extents.y, half_extents.x, half_extents.z));
    cd.position = bounds.first + ((bounds.second - bounds.first) * 0.5f);
    //cd.position = glm::vec3(cd.position.x, cd.position.z, -cd.position.y);
    //cd.position *= -1;
    //cd.position.z *= -1;
    return cd;
}
