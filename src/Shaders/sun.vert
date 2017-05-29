#version 330

in vec2 vertex;

void main()
{
    gl_Position = vec4(vec3(vertex, 0), 1);
}
