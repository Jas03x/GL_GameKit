#version 330

in vec2 uv_coords[11];

uniform sampler2D tex;

out vec4 color;

void main()
{
    color = vec4(0.0);
    color += texture(tex, uv_coords[ 0])  * 0.0093;
    color += texture(tex, uv_coords[ 1])  * 0.028002;
    color += texture(tex, uv_coords[ 2])  * 0.065984;
    color += texture(tex, uv_coords[ 3])  * 0.121703;
    color += texture(tex, uv_coords[ 4])  * 0.175713;
    color += texture(tex, uv_coords[ 5])  * 0.198596;
    color += texture(tex, uv_coords[ 6])  * 0.175713;
    color += texture(tex, uv_coords[ 7])  * 0.121703;
    color += texture(tex, uv_coords[ 8])  * 0.065984;
    color += texture(tex, uv_coords[ 9])  * 0.028002;
    color += texture(tex, uv_coords[10])  * 0.0093;
}
