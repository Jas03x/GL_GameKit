#ifndef BT_UTILS_H
#define BT_UTILS_H

#include <LinearMath/btVector3.h>
#include "Math3D.h"

namespace bt
{
	// simple conversion from glm to bullet physics
	inline btVector3 vec3(const glm::vec3& v)
	{
		return btVector3(v.x, v.y, v.z);
	}
	inline btVector3 vec3(const glm::vec4& v) { return vec3(glm::vec3(v)); }
	inline btVector3 vec3(const float x, const float y, const float z) { return vec3(x, y, z); }
}

#endif