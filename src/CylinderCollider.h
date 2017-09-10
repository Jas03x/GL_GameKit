#ifndef CYLINDER_COLLIDER_H
#define CYLINDER_COLLIDER_H

#include "Math3d.h"
#include "Physics.h"
#include "Collider.h"
#include "ColliderUtilities.h"

class CylinderShape : public Collider
{
public:
	CylinderShape(const glm::vec3& half_extents);
	~CylinderShape() {}

	static ShapeData getShape(const MeshDescriptor& descriptor, const std::vector<int>* faces = NULL);
};

#endif /* CYLINDER_COLLIDER_H */
