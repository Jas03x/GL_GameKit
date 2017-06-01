#include "PointLight.h"

GLuint PointLight::_vao;
GLuint PointLight::_vbo;
unsigned int PointLight::_vertex_count;

PointLight::PointLight(const glm::vec3& _position, const glm::vec3& _size, const glm::vec3& _color)
{
    this->position = _position;
    this->size = _size;
    this->color = _color;
}

void PointLight::_genVAO()
{
#ifdef _WIN32
    const char* LIGHT_SPHERE_PATH = "C:\\Users\\Jas\\Documents\\GameKit\\src\\Data\\UnitSphere.obj";
#else
    const char* LIGHT_SPHERE_PATH = "/Users/Jas/Documents/Libraries/GL_Engine/src/Data/UnitSphere.obj";
#endif
    
    OBJ_Loader loader = OBJ_Loader(LIGHT_SPHERE_PATH, OBJ_Loader::VN);
    std::vector<float> vertex_buffer;
    vertex_buffer.reserve(loader.getIndices().size() * 3);
    for (unsigned int i = 0; i < loader.getIndices().size(); i++)
    {
        const float* v = &loader.getVertices().at(loader.getIndices().at(i).x - 1)[0];
        vertex_buffer.insert(vertex_buffer.end(), v, v + 3);
    }
    
    _vertex_count = (unsigned int) vertex_buffer.size() / 3;
    
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_buffer.size(), &vertex_buffer[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PointLight::_deleteVAO()
{
    if (glIsVertexArray(_vao) == GL_TRUE) glDeleteVertexArrays(1, &_vao);
    if (glIsBuffer(_vbo) == GL_TRUE) glDeleteBuffers(1, &_vbo);
}
