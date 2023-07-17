#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 lightPos;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

layout(set = 1, binding = 1) uniform sampler2D tex;

const float beta = 0.1f;
const float g = 8;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//vec3 Ms - specular color of the surface
	//float gamma - Exponent for power specular term
	vec3 Lambert =Md*clamp(dot(L,N),0.0,1.0);
	vec3 rx = -reflect(L,N);
	vec3 Phong = Ms*pow(clamp(dot(V,rx),0.0,0.99f),gamma);

	vec3 Lambert_Phong_light =Lambert + Phong;
	return Lambert_Phong_light;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);

	vec3 lightDir = normalize(gubo.lightPos - fragPos);
	vec3 lightColor = gubo.lightColor.rgb;

	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, vec3(1.0f), 160.0f);
	vec3 Ambient = texture(tex, fragUV).rgb * 0.05f;

	outColor = vec4(clamp(0.95 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}

