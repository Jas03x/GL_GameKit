#include "ConvexHullCollider.h"

ConvexHullCollider::ConvexHullCollider(const MeshDescriptor& descriptor, const std::vector<int>* face_array)
{
	if (descriptor.getMeshLoader().getBoneNames().size() > 0)
		this->constructFromDynamicMesh(descriptor, face_array);
	else this->constructFromStaticMesh(descriptor, face_array);
}

void ConvexHullCollider::constructFromStaticMesh(const MeshDescriptor& descriptor, const std::vector<int>* face_array)
{
	const MeshLoader& data = descriptor.getMeshLoader();
	//const glm::mat4 local_transform = descriptor.getTransform().toMatrix() * glm::scale(descriptor.getScale());
	const glm::mat4 local_transform = glm::scale(descriptor.getScale());
	VectorTree vertex_tree;
	const std::vector<int>& faces = face_array ? *face_array : data.getFaces();
	for (unsigned int i = 0; i < faces.size(); i++) {
		const unsigned int face = faces[i];
		glm::vec3 vertex = glm::vec3(local_transform * data.getNodeTransforms()[data.getNodeIndices()[face]] * glm::vec4(data.getVertices()[face], 1));
		vertex_tree.insert(vertex);
	}

	std::vector<glm::vec3> vertex_array;
	vertex_tree.toArray(vertex_array);
	btConvexHullShape* chs = new btConvexHullShape();
	// TODO: Perhaps optimize this: read directly from the vertex tree rather than converting it into an array
	for (unsigned int i = 0; i < vertex_array.size(); i++) {
		chs->addPoint(btVector3(vertex_array[i].x, vertex_array[i].y, vertex_array[i].z), false);
	}
	//chs->recalcLocalAabb();
	btShapeHull* hull = new btShapeHull(chs);
	btScalar margin = chs->getMargin();
	hull->buildHull(margin);
	this->shape = new btConvexHullShape(&hull->getVertexPointer()->getX(), hull->numVertices());

	delete chs;
	delete hull; // TODO: MAYBE THIS SHOULD NOT BE DELETED?! IT MIGHT NEED TO STAY IN MEMORY!!
}

void ConvexHullCollider::constructFromDynamicMesh(const MeshDescriptor& descriptor, const std::vector<int>* face_array)
{
	// TODO: IMPLEMENT!!!
	// NOTE: VERY SIMILAR PROCESS TO THE SOFTBODY CONSTRUCTION!!!
	printf("Error: Convex hull collider construction from dynamic mesh not yet implemented!\n");
	throw - 1;
}

