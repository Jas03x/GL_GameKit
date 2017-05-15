#version 330

in vec2 _uv;

uniform sampler2D texture_id;

out vec4 color;

void main()
{
    color = texture(texture_id, _uv);
}
