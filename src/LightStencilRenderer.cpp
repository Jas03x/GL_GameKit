#include "LightStencilRenderer.h"

void LightStencilRenderer::load()
{
    ShaderSource source = ShaderSource(INT_SHDR("light_stencil.vert"), INT_SHDR("light_stencil.frag"));
    this->source(source);
    this->bindAttributeLocation(0, "vertex");
    this->link(source);
    this->mvp = this->getUniform("mvp");
}

void LightStencilRenderer::render(const PointLight& light)
{
    this->bind();
    PointLight::_bindVAO();
    glm::mat4 matrix = Camera::vp * glm::translate(light.position) * glm::scale(light.size);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &matrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, PointLight::_getArrayVertexCount());
    glBindVertexArray(0);
}

void LightStencilRenderer::destroy()
{
    Shader::destroy();
}
