#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 lightPos;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

layout(set = 0, binding = 1) uniform sampler2D toonLight;

const float beta = 1.0f;
const float g = 3;	

float t(float normDot) {
    normDot = clamp(abs(normDot), 0.01, 0.999);
    normDot = texture(toonLight, vec2(normDot, 0.5)).r;
    return normDot;
}

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//vec3 Ms - specular color of the surface
	//float gamma - Exponent for power specular term

	// Lambert's BRDF only has the diffusion component,
	// it only depends on the color of the object and
	// the angle between the norm of the surface and the light
	// (clamped to 0 in cas of non incidence)
	vec3 Lambert = Md * max(t(dot(L, N)), 0);

	// To add the reflection component an additional model is needed.
	// Here, the Phong BRDF takes into account the angle between the
	// reflection direction and the view direction, to recreate a reflection
	// the GAMMA variable defines how "focused" is this reflaction, bringing
	// the value down to 0 quicker
	vec3 R = 2 * N * dot(L, N) - L;
	vec3 Phong = Ms * (pow(clamp(t(dot(V, R)), 0, 1), gamma));

	// Then add the two
	return Lambert + Phong;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	
	vec3 lightDir = normalize(gubo.lightPos - fragPos);
    vec3 lightColor = gubo.lightColor.rgb;

    vec3 baseColor = vec3(1,0,1);

	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, baseColor, vec3(1.0f), 60.0f);
	vec3 Ambient = baseColor * 0.1f;
	
	outColor = vec4(clamp(0.95 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}