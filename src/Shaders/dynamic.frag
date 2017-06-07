#version 330

in vec2 _uv;
in vec3 _normal;
in float _texture_id;

uniform sampler2D textures[4];

out vec4 diffuse_out;
out vec3 normal_out;
out vec4 light_out;

void main()
{
	vec4 color = texture(textures[int(_texture_id)], _uv);
    diffuse_out = color;
	normal_out = _normal;
	light_out = color * 0.75;
}
