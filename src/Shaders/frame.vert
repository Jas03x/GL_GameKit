#version 330

in vec2 vertex;

out vec2 uv;

void main()
{
    gl_Position = vec4(vec3(vertex, 0), 1);
    uv = (vertex + vec2(1)) * 0.5;
}
