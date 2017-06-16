#include "SceneRenderer.h"

_SceneRenderer SceneRenderer;

void _SceneRenderer::initalize()
{
	ShaderSource source = ShaderSource(INT_SHDR("scene.vert"), INT_SHDR("scene.frag"));
	this->source(source);
	this->bindAttributeLocation(0, "vertex");
	this->bindAttributeLocation(1, "normal");
	this->bindAttributeLocation(2, "uv");
	this->bindAttributeLocation(3, "node_index");
	this->bindAttributeLocation(4, "texture_index");
	this->bindFragDataLocation(DSFramebuffer::DIFFUSE_TEXTURE, "diffuse_out");
	this->bindFragDataLocation(DSFramebuffer::NORMAL_TEXTURE, "normal_out");
	this->bindFragDataLocation(DSFramebuffer::LIGHT_TEXTURE, "light_out");
	this->link(source);
	this->vertex_matrices = this->getUniform("vertex_matrices");
	this->normal_matrices = this->getUniform("normal_matrices");
	this->textures[0] = this->getUniform("textures[0]");
	this->textures[1] = this->getUniform("textures[1]");
	this->textures[2] = this->getUniform("textures[2]");
	this->textures[3] = this->getUniform("textures[3]");
}

void _SceneRenderer::render(const Scene& scene)
{
	this->bind();
	scene.bind();
	for (unsigned int i = 0; i < scene.getTextureCount(); i++)
		scene.getTextures()[i].bind(this->textures[i], i);

	glm::mat4 vmatrices[32];
	glm::mat4 nmatrices[32];
	glm::mat4 mvp = Camera::getMatrix() * scene.model_matrix;
	glm::mat4 mv = Camera::getViewMatrix() * scene.model_matrix;
    
	for (unsigned int i = 0; i < scene.getNodeTransforms().size(); i++) {
		vmatrices[i] = mvp * scene.getNodeTransforms().at(i);
		nmatrices[i] = glm::inverse(glm::transpose(mv * scene.getNodeTransforms().at(i)));
	}
	glUniformMatrix4fv(this->vertex_matrices, (unsigned int) scene.getNodeTransforms().size(), GL_FALSE, &vmatrices[0][0][0]);
	glUniformMatrix4fv(this->normal_matrices, (unsigned int) scene.getNodeTransforms().size(), GL_FALSE, &nmatrices[0][0][0]);

	glDrawArrays(GL_TRIANGLES, 0, scene.getVertexCount());
	glBindVertexArray(0);
}

void _SceneRenderer::destroy()
{
	Shader::destroy();
}
