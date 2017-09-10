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

class ConvexHullCollider : public Collider
{
private:

protected:
	void constructFromStaticMesh(const MeshDescriptor& descriptor, const std::vector<int>* face_array = NULL);
	void constructFromDynamicMesh(const MeshDescriptor& descriptor, const std::vector<int>* face_array = NULL);

public:
	ConvexHullCollider() {}
	ConvexHullCollider(const MeshDescriptor& descriptor, const std::vector<int>* face_array = NULL);
	~ConvexHullCollider() {}
};

#endif /*CONVEX_HULL_COLLIDER*/