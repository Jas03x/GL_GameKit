#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4 camera_matrix;

out vec2 _uv;
out vec3 _normal;

void main()
{
    gl_Position = camera_matrix * vec4(vertex, 1);
    _uv = uv;
    _normal = normalize(normal);
}
