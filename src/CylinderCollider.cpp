#include "CylinderCollider.h"

CylinderShape::CylinderShape(const glm::vec3& half_extents)
{
	this->shape = new btCylinderShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
}

ShapeData CylinderShape::getShape(const MeshDescriptor& descriptor, const std::vector<int>* faces)
{
	std::pair<glm::vec3, glm::vec3> bounds = ColliderUtilities::calculate_bounds(descriptor, faces);

	ShapeData cd;
	glm::vec3 half_extents = glm::abs(bounds.second * bounds.first) * 0.5f;

	// TODO: YOU MIGHT NEED TO ADD AN ENUM SYSTEM TO MARK WHICH ORDER THE CYLINDER SHOULD BE CREATED WITH
	// THIS ORDER ISSUE IS THE REASON WHY YOU HAD TO CREATE THIS CYLINDER IN YXZ FORMAT (because the cylinder was rotated!!!)
	cd.shape = new CylinderShape(half_extents);
	cd.position = bounds.first + ((bounds.second - bounds.first) * 0.5f);
	//cd.position = glm::vec3(cd.position.x, cd.position.z, -cd.position.y);
	//cd.position *= -1;
	//cd.position.z *= -1;
	return cd;
}
