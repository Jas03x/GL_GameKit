#version 330

uniform vec2 screen_size;
uniform vec3 sun_position;
uniform vec3 sun_color;
uniform mat4 inv_proj_matrix;

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D depth_texture;

out vec4 diffuse_out;

void main()
{
    vec2 texcoord = vec2(gl_FragCoord.x / screen_size.x, gl_FragCoord.y / screen_size.y);
    
    vec4 clipSpaceLocation;
    clipSpaceLocation.xy = texcoord * 2.0 - 1.0;
    clipSpaceLocation.z = texture(depth_texture, texcoord).r * 2.0 - 1.0;
    clipSpaceLocation.w = 1.0;
    vec4 homogenousLocation = inv_proj_matrix * clipSpaceLocation;
    vec3 view_space = homogenousLocation.xyz / homogenousLocation.w;
    
    vec3 diffuse = texture(diffuse_texture, texcoord).rgb;
    vec3 normal = texture(normal_texture, texcoord).rgb;

    vec3 eye_direction_cameraspace = vec3(0,0,0) - view_space;
    vec3 sun_direction_cameraspace = normalize(sun_position + eye_direction_cameraspace);
    eye_direction_cameraspace = normalize(eye_direction_cameraspace);

    float cosTheta = clamp(dot(normal, sun_direction_cameraspace), 0, 1);
    float cosAlpha = clamp(dot(eye_direction_cameraspace, reflect(-sun_direction_cameraspace, normal)), 0, 1);
    
    diffuse_out = vec4(diffuse * 0.2 + sun_color * cosTheta * 0.25 + 0.1 * vec3(1) * cosAlpha, 0.1);
}
