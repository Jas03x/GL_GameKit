#include "Scene.h"

Scene::Scene(const char* path, const char* name)
{
	std::string source = std::string(path) + name;
	ColladaLoader loader = ColladaLoader(source.c_str());

	if (loader.getTextures().size() > SCENE_MAX_TEXTURES) {
		printf("Maximum texture limit %i exceeded in collada file [%s].\n", SCENE_MAX_TEXTURES, source.c_str());
		throw - 1;
	}

	size_t vc = loader.getVertices().size();

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vc * 10, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vc * 3, &loader.getVertices()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 3, sizeof(float) * vc * 3, &loader.getNormals()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 6, sizeof(float) * vc * 2, &loader.getUVs()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 8, sizeof(float) * vc, &loader.getNodeIndices()[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 9, sizeof(float) * vc, &loader.getTextureIndices()[0]);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(1); // normals
	glEnableVertexAttribArray(2); // uvs
	glEnableVertexAttribArray(3); // node indices
	glEnableVertexAttribArray(4); // texture indices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 6));
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 8));
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vc * 9));
	// INSERT MATRIX DATA HERE
	// SLOT 3 = matrix index

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->node_transforms.reserve(loader.getMeshNames().size()); // reserve the memory before hand so that the vector doesn't move and leave dangling references
	for (unsigned int i = 0; i < loader.getMeshNames().size(); i++)
	{
		const std::string& name = loader.getMeshNames().at(i);
		this->node_transforms.push_back(loader.getNodeTransforms().at(name));
		this->nodes[name] = &this->node_transforms.back();
	}

	// load the textures
	this->textures = new Texture[loader.getTextures().size()];
	int i = 0;
	std::vector<std::string>::const_iterator it = loader.getTextures().begin();
	for (; it != loader.getTextures().end(); it++, i++) {
		std::string t_path = std::string(path) + it->c_str();
		printf("%i: %s\n", i, t_path.c_str());
		this->textures[i].load(t_path.c_str());
	}

	this->vertex_count = (unsigned int) loader.getVertices().size();
	this->texture_count = (unsigned int) loader.getTextures().size();
	this->model_matrix = glm::mat4(1.0f);
}
void Scene::destroy()
{
	if (this->textures != NULL) delete[] this->textures;
	if (glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
	if (glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
}
