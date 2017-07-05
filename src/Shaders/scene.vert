#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in uint node_index;
in uint texture_index;

uniform mat4 vertex_matrices[32];
uniform mat4 normal_matrices[32];

out vec2 _uv;
out vec3 _normal;
flat out uint _texture_index;

void main()
{
	gl_Position = vertex_matrices[node_index] * vec4(vertex, 1);
	_normal = normalize(vec3(normal_matrices[node_index] * vec4(vertex, 1)));
	_uv = uv;
	_texture_index = texture_index;
}
