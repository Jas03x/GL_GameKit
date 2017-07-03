#include "Scene.h"

void Scene::load(const char* path)
{
	ColladaLoader loader = ColladaLoader(path);

	if (loader.getTextures().size() > SCENE_MAX_TEXTURES) {
		printf("Maximum texture limit %i exceeded in collada file [%s].\n", SCENE_MAX_TEXTURES, path);
		throw - 1;
	}

	size_t vc = loader.getVertices().size();

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vc * 10, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,                      sizeof(float) * vc * 3, &loader.getVertices()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 3, sizeof(float) * vc * 3, &loader.getNormals()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 6, sizeof(float) * vc * 2, &loader.getUVs()[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 8, sizeof(float) * vc * 1, &loader.getNodeIndices()[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vc * 9, sizeof(float) * vc * 1, &loader.getTextureIndices()[0]);

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

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(loader.getNodeTransforms().size() > SCENE_MAX_NODES) {
        printf("Error: Scene [%s] exceeds max scene count [%i]!\n", path, SCENE_MAX_NODES);
        throw -1;
    }
	this->node_transforms.reserve(loader.getNodeTransforms().size()); // reserve the memory before hand so that the vector doesn't move and leave dangling references
	for (unsigned int i = 0; i < loader.getNodeTransforms().size(); i++)
	{
		const std::string& name = loader.getNodeNames().at(i);
		this->node_transforms.push_back(loader.getNodeTransforms().at(name));
		this->nodes[name] = &this->node_transforms.back();
	}

	// load the textures
	this->textures = new Texture[loader.getTextures().size()];
    std::string file_path = std::string(path);
    file_path = file_path.substr(0, file_path.find_last_of("/\\") + 1);
    for(unsigned int i = 0; i < loader.getTextures().size(); i++)
    {
        std::string t_path = file_path + loader.getTextures()[i];
        this->textures[i] = Texture(t_path.c_str());
    }

	this->vertex_count = (unsigned int) loader.getVertices().size();
	this->texture_count = (unsigned int) loader.getTextures().size();
    
    this->scale = glm::vec3(1);
    this->position = glm::vec3(0);
    this->rotation = glm::quat(0, 0, 0, 1);
}

void Scene::destroy()
{
	if (this->textures != NULL) delete[] this->textures;
	if (glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
	if (glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
}
