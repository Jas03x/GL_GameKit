#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in uint node_index;
in uint texture_id;
in vec4 bone_weights;
in uvec4 bone_indices;

uniform mat4 bones[16];
uniform mat4 nodes[16];
uniform mat4 mvp_matrix;
uniform mat4 normal_matrix;

out vec2 _uv;
out vec3 _normal;
flat out uint _texture_id;

void main()
{
    // initalize bone to an identity matrix if the mesh has no bones
    // if a vertex's 4 weights do not sum to 1, there will be problems
    // each vertex _MUST_ have 4 weights which sum to 1
    mat4 bone = (1.0 - bone_weights[0] - bone_weights[1] - bone_weights[2] - bone_weights[3]) * nodes[node_index];
    bone += bones[bone_indices[0]] * bone_weights[0];
    bone += bones[bone_indices[1]] * bone_weights[1];
    bone += bones[bone_indices[2]] * bone_weights[2];
    bone += bones[bone_indices[3]] * bone_weights[3];
    
    // mvp * inverse * offset * bindpose * bone
    vec4 v = bone * vec4(vertex, 1);
    gl_Position = mvp_matrix * vec4(v.xyz, 1);
    //gl_Position = mvp_matrix * vec4(v.x, v.z, -v.y, 1);
	_normal = normalize(vec3(normal_matrix * vec4(vertex, 1)));
    _uv = uv;
    _texture_id = texture_id;
}
