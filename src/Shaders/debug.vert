#version 330

in vec3 vertex;
uniform mat4 vp_matrix;

void main()
{
    gl_Position = vp_matrix * vec4(vertex, 1);
}
