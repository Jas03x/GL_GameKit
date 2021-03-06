#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in uint m_index;

uniform mat4 vertex_matrix;
uniform mat4 normal_matrix;

out vec2 _uv;
out vec3 _normal;
flat out uint _m_index;

void main()
{
    gl_Position = vertex_matrix * vec4(vertex, 1);
    _uv = uv;
    _normal = normalize(vec3(normal_matrix * vec4(vertex, 1)));
    _m_index = m_index;
}
