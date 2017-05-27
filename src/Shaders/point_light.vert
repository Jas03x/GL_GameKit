#version 330

in vec3 vertex;

uniform mat4 mvp_matrix;

void main()
{
	gl_Position = mvp_matrix * vec4(vertex, 1);
}
