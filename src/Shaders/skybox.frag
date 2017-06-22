#version 330

in vec3 uv;
uniform samplerCube skymap;
out vec4 diffuse_out;

void main()
{
    diffuse_out = texture(skymap, uv);
}
