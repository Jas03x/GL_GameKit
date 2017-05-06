#version 330

in vec2 uv_coords[5];

uniform sampler2D tex;

out vec4 color;

void main()
{
    color = vec4(0.0);
    color += texture(tex, uv_coords[0])  * 0.06136;
    color += texture(tex, uv_coords[1])  * 0.24477;
    color += texture(tex, uv_coords[2])  * 0.38774;
    color += texture(tex, uv_coords[3])  * 0.24477;
    color += texture(tex, uv_coords[4])  * 0.06136;
}
