#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <vector>

#include "GL.h"
#include "Math3d.h"
#include "Texture.h"
#include "ColladaLoader.h"

#define SCENE_MAX_TEXTURES 4

// TODO: Add node support
class Scene
{
private:
	GLuint vao;
	GLuint vbo;
	Texture* textures;
	unsigned int vertex_count;
	unsigned int texture_count;

	std::map<std::string, glm::mat4*> nodes; // the names of each node in the map
	std::vector<glm::mat4> node_transforms; // the corresponding matrices to the node

public:
	glm::mat4 model_matrix;

	Scene() { this->textures = NULL; }
	void destroy();

	void load(const char* path, const char* name);
	inline void bind() const { glBindVertexArray(this->vao); }
	inline unsigned int getVertexCount() const { return this->vertex_count; }
	inline unsigned int getTextureCount() const { return this->texture_count; }
	const Texture* getTextures() const { return this->textures; }

	inline glm::mat4* getNodeTransform(const std::string& name) { return this->nodes.at(name); } // non-constant version
	inline const glm::mat4* getNodeTransform(const std::string& name) const { return this->nodes.at(name); } // constant version
	inline const std::vector<glm::mat4>& getNodeTransforms() const { return this->node_transforms; }
};

#endif
