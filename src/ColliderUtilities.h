#ifndef COLLIDER_UTILITIES_H
#define COLLIDER_UTILITIES_H

#include <utility>

#include "Math3D.h"
#include "MeshDescriptor.h"

namespace ColliderUtilities
{
	std::pair<glm::vec3, glm::vec3> _calculate_static_mesh_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces = NULL);
	std::pair<glm::vec3, glm::vec3> _calculate_dynamic_mesh_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces = NULL);
	// calculates the bounds of a mesh
	// returns the pair <min, max>
	std::pair<glm::vec3, glm::vec3> calculate_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces = NULL);
}

#endif /*COLLIDER_UTILITIES_H*/
