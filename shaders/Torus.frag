#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec2 fragUV;
layout(location =2) in vec3 fragNorm;
layout(location =3) in vec3 fragTan;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 lightPos;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

layout(set = 1, binding = 1) uniform sampler2D tex;

const float beta = 0.1f;
const float g = 8;

const float gamma = 160.0f;	// cosine power for the Blinn specular reflection

void main() {

	vec3 Norm = normalize(fragNorm);
	vec3 N = normalize(fragNorm);

	vec3 lightPos = gubo.lightPos;
	vec3 lightDir = normalize(lightPos - fragPos);

	vec3 V = normalize(gubo.eyePos - fragPos);	// viewer direction
	vec3 MD = texture(tex, fragUV).rgb;			// diffuse color
	vec3 MA = MD;								// ambient color
	vec3 MS = vec3(1);							// specular color
	vec3 ME = vec3(0.0);						// emission color

	// Point light (Light model as in Assignment 11.3)
	vec3 PointLight = pow(g / distance(lightPos, fragPos), beta) * gubo.lightColor.xyz;

	// Compute Lambert + Blinn model
	// (Diffusion + Specular model same as in Assignment 12)
	vec3 Lambert = MD * clamp(dot(lightDir, N), 0.0f, 0.5f);
	vec3 H = normalize(lightDir + V);
	vec3 Blinn = MS * pow(clamp(dot(N, H), 0, .96f), gamma); //clamped at 0.96 to prevent a "halo" from forming on the torus at specific orientations of the target
	
	// Add all components
	outColor = vec4(
		clamp(
			(Lambert	// Diffusion Model
				+ Blinn) // Specular Model
			* PointLight // Only Diffusion and Specular depends on light model
			+ ME,	// Emission component only depends on the emission of the object
			0, 1),
		1.0f);	// output color
}