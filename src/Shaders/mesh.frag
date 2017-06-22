#version 330

in vec2 _uv;
in vec3 _normal;

uniform sampler2D texture_id;

out vec4 diffuse_out;
out vec3 normal_out;
out vec4 light_out;

void main()
{
    vec4 color = texture(texture_id, _uv);
    diffuse_out = color;
    normal_out = _normal;
    light_out = color * 0.5;
}
