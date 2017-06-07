#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in float texture_id;

uniform mat4 vertex_matrix;
uniform mat4 normal_matrix;

out vec2 _uv;
out vec3 _normal;
out float _texture_id;

void main()
{
    gl_Position = vertex_matrix * vec4(vertex, 1);
	_normal = normalize(vec3(normal_matrix * vec4(vertex, 1)));
    _uv = uv;
    _texture_id = texture_id;
}
