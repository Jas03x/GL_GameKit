#version 330

in vec3 vertex;
uniform mat4 matrix;
out vec3 uv;

void main()
{
    gl_Position = (matrix * vec4(vertex, 1));
    uv = vertex;
}
