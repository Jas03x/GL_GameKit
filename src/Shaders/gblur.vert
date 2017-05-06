#version 330

in vec2 vertex;

uniform vec2 direction;
uniform float width;

out vec2 uv_coords[5];

void main()
{
    gl_Position = vec4(vec3(vertex, 0), 1);
    
    vec2 center = (vertex + vec2(1)) * 0.5;
    float size = 1.0 / width;
    for(int i = -2; i <= 2; i++)
    {
        uv_coords[i+2] = center + vec2(size * i * direction.x, size * i * direction.y);
    }
}
