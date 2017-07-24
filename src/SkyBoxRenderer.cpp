#include "SkyBoxRenderer.h"

_SkyBoxRenderer SkyBoxRenderer;

void _SkyBoxRenderer::initalize()
{
    ShaderSource source = ShaderSource(INT_SHDR("skybox.vert"), INT_SHDR("skybox.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->bindFragDataLocation(DSFramebuffer::LIGHT_TEXTURE, "diffuse_out");
    this->link(source);
    this->matrix = this->getUniform("matrix");
    this->skymap = this->getUniform("skymap");
    
    OBJ_Loader loader = OBJ_Loader(INT_DATA("UnitCube.obj"), OBJ_Loader::V);
    std::vector<glm::vec3> vertices;
    vertices.reserve(loader.getIndices().size());
    for(unsigned int i = 0; i < loader.getIndices().size(); i++)
        vertices.push_back(loader.getVertices()[loader.getIndices()[i].x - 1]);
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0][0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertex_count = (unsigned int) vertices.size();
}

void _SkyBoxRenderer::render(const SkyBox& skybox)
{
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    
    this->bind();
    glBindVertexArray(this->vao);
    glm::mat4 vp = Camera::getProjectionMatrix() * glm::mat4(glm::mat3(Camera::getViewMatrix()));
    glUniformMatrix4fv(this->matrix, 1, GL_FALSE, &vp[0][0]);
    skybox.bind(this->skymap, 0);
    glDrawArrays(GL_TRIANGLES, 0, this->vertex_count);
    glBindVertexArray(0);
    
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}

void _SkyBoxRenderer::destroy()
{
    Shader::destroy();
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
}
