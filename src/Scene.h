#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <stdio.h>

#include "GL.h"
#include "Math3d.h"
#include "Texture.h"
#include "ColladaLoader.h"
#include "Collider.h"
#include "RigidBody.h"
#include "SoftBody.h"
#include "Transform.h"

#define SCENE_MAX_TEXTURES 4
#define SCENE_MAX_NODES 32

// TODO: Add node support
class Scene
{
protected:
	GLuint vao;
	GLuint vbo;
	
    glm::vec3 scale;
    unsigned int vertex_count;
	unsigned int texture_count;
    
    Texture* textures;

    Transform transformation;
    
	std::map<std::string, unsigned int> nodes; // the names of each node in the map
	std::vector<glm::mat4> node_transforms; // the corresponding matrices to the node
    std::vector<Transform> transformations; // the per mesh transformations for bullet physics

public:
	Scene() { this->textures = NULL; }
    Scene(const char* path, const glm::vec3& _scale = glm::vec3(1.0f)) { this->load(ColladaLoader(path), _scale); }
    void load(const ColladaLoader& loader, const glm::vec3& _scale = glm::vec3(1.0f));
	void destroy();

	inline void bind() const { glBindVertexArray(this->vao); }
	inline unsigned int getVertexCount() const { return this->vertex_count; }
	inline unsigned int getTextureCount() const { return this->texture_count; }
	const Texture* getTextures() const { return this->textures; }
    
    inline glm::mat4 getMatrix() const { return this->transformation.toMatrix() * glm::scale(this->scale); }

    // Node data:
	inline const std::vector<glm::mat4>& getNodeTransforms() const { return this->node_transforms; }
    inline const std::vector<Transform>& getTransformations() const { return this->transformations; }
    
    inline Transform& getTransformation(const std::string& name) { return this->transformations[this->nodes.at(name)]; }
    inline const Transform& getTransformation(const std::string& name) const { return this->transformations[this->nodes.at(name)]; }
    
    inline glm::mat4& getNodeTransform(const std::string& name) { return this->node_transforms[this->nodes.at(name)]; } // non-constant version
    inline const glm::mat4& getNodeTransform(const std::string& name) const { return this->node_transforms[this->nodes.at(name)]; } // constant version
};

#endif
