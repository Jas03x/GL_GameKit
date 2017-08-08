#ifndef CONVEX_HULL_COLLIDER
#define CONVEX_HULL_COLLIDER

#include <stdio.h>

#include "Mesh.h"
#include "RigidBody.h"
#include "MeshLoader.h"
#include "VectorTree.h"
#include "MeshDescriptor.h"
#include "PhysicsConfiguration.h"

#include <BulletCollision\CollisionShapes\btShapeHull.h>
#include <BulletCollision\CollisionShapes\btConvexHullShape.h>

class ConvexHullCollider : public RigidBody
{
private:

protected:
	void constructFromStaticMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia);
	void constructFromDynamicMesh(const MeshDescriptor& descriptor, const float mass, const glm::vec3& inertia);

public:
	ConvexHullCollider() {}
	ConvexHullCollider(const MeshDescriptor& descriptor, const float mass = 0, const glm::vec3& inertia = glm::vec3(0));
	~ConvexHullCollider();
};

#endif /*CONVEX_HULL_COLLIDER*/