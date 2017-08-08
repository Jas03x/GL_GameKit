#include "ColliderUtilities.h"

#define MAX_COMPARISON(x, v) if((x) > (v)) (v) = (x);
#define MIN_COMPARISON(x, v) if((x) < (v)) (v) = (x);
#define UPPER_BOUND 100000

std::pair<glm::vec3, glm::vec3> ColliderUtilities::_calculate_static_mesh_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces)
{
	const MeshLoader& data = descriptor.getMeshLoader();
	const glm::mat4 local_transform = descriptor.getTransform().toMatrix() * glm::scale(descriptor.getScale());
	glm::vec3 m = glm::vec3(UPPER_BOUND);
	glm::vec3 M = glm::vec3(-UPPER_BOUND);
	for (unsigned int i = 0; i < data.getFaces().size(); i++) {
		const unsigned int face = data.getFaces()[i];
		glm::vec3 vec = glm::vec3(local_transform * data.getNodeTransforms()[data.getNodeIndices()[face]] * glm::vec4(data.getVertices()[face], 1));
		MAX_COMPARISON(vec.x, M.x);
		MAX_COMPARISON(vec.y, M.y);
		MAX_COMPARISON(vec.z, M.z);
		MIN_COMPARISON(vec.x, m.x);
		MIN_COMPARISON(vec.y, m.y);
		MIN_COMPARISON(vec.z, m.z);
	}
	return std::pair<glm::vec3, glm::vec3>(m, M);
}

std::pair<glm::vec3, glm::vec3> ColliderUtilities::_calculate_dynamic_mesh_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces)
{
	const MeshLoader& loader = descriptor.getMeshLoader();
	std::vector<glm::mat4> bone_cache;
	bone_cache.reserve(loader.getBoneNames().size());
	for (unsigned int i = 0; i < loader.getBoneNames().size(); i++)
		bone_cache.push_back(loader.getNodeTransforms()[i] * loader.getBoneOffsets()[i]);
	const glm::mat4 local_transform = descriptor.getTransform().toMatrix() * glm::scale(descriptor.getScale());
	
	const std::vector<int>& faces = _faces ? *_faces : loader.getFaces();
	glm::vec3 m = glm::vec3( UPPER_BOUND);
	glm::vec3 M = glm::vec3(-UPPER_BOUND);
	for (unsigned int i = 0; i < faces.size(); i++) {
		const glm::vec3& vertex = loader.getVertices()[faces[i]];
		const MeshLoader::BoneIndex& index = loader.getBoneIndices()[faces[i]];
		const glm::vec4& weight = loader.getBoneWeights()[faces[i]];
		glm::mat4 joint =
			weight.x * bone_cache[index.b0] +
			weight.y * bone_cache[index.b1] +
			weight.z * bone_cache[index.b2] +
			weight.w * bone_cache[index.b3];

		glm::vec3 vec = glm::vec3(local_transform * joint * glm::vec4(vertex, 1));
		MAX_COMPARISON(vec.x, M.x);
		MAX_COMPARISON(vec.y, M.y);
		MAX_COMPARISON(vec.z, M.z);
		MIN_COMPARISON(vec.x, m.x);
		MIN_COMPARISON(vec.y, m.y);
		MIN_COMPARISON(vec.z, m.z);
	}

	return std::pair<glm::vec3, glm::vec3>(m, M);
}

// calculates the bounds of a mesh
// returns the pair <min, max>
std::pair<glm::vec3, glm::vec3> ColliderUtilities::calculate_bounds(const MeshDescriptor& descriptor, const std::vector<int>* _faces)
{
	if (descriptor.getMeshLoader().getBoneNames().size() > 0) return _calculate_dynamic_mesh_bounds(descriptor, _faces);
	else return _calculate_static_mesh_bounds(descriptor, _faces);
}
