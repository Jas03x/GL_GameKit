#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "GL.h"
#include "GLM.h"
#include "OBJ_Loader.h"

class PointLight
{
private:
    // global data:
    static GLuint _vao;
    static GLuint _vbo;
    static unsigned int _vertex_count;
    
public:
    static void _genVAO();
    static void _deleteVAO();
    inline static void _bindVAO() { glBindVertexArray(_vao); }
    inline static unsigned int _getArrayVertexCount() { return _vertex_count; }
    
    // local data:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 color;
    
    PointLight(const glm::vec3& _position, const glm::vec3& _size, const glm::vec3& _color);
};

#endif
