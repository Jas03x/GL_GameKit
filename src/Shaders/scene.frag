#version 330

in vec2 _uv;
in vec3 _normal;
flat in uint _texture_index;

uniform sampler2D textures[4];

out vec4 diffuse_out;
out vec3 normal_out;
out vec4 light_out;

void main()
{
	vec4 color = texture(textures[_texture_index], _uv);
	diffuse_out = color;
	light_out = color * 0.75;
	normal_out = _normal;
}
