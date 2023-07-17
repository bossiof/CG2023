#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;
layout(location = 3) in vec4 fragTan;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 lightPos;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

layout(set = 1, binding = 1) uniform sampler2D tex;
layout(set = 1, binding = 2) uniform sampler2D normMap;

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
	vec3 Phong = Ms*pow(clamp(dot(V,rx),0.0,1.0),gamma);

	vec3 Lambert_Phong_light =Lambert + Phong;
	return Lambert_Phong_light;
}

const float cosout = 0.5;	// cosine of the outer angle of the spotlight
const float cosin  = 0.95;	// cosine of the inner angle of the spotlight

const float gamma = 160.0f;	// cosine power for the Blinn specular reflection

// coefficients for the spehrical harmonics ambient light term
const vec3 C00  = vec3( .38f, .43f, .45f)/8.0f;
const vec3 C1m1 = vec3( .29f, .36f, .41f)/8.0f;
const vec3 C10  = vec3( .04f, .03f, .01f)/8.0f;
const vec3 C11  = vec3(-.10f,-.10f,-.09f)/8.0f;
const vec3 C2m2 = vec3(-.06f,-.06f,-.04f)/8.0f;
const vec3 C2m1 = vec3( .01f,-.01f,-.05f)/8.0f;
const vec3 C20  = vec3(-.09f,-.13f,-.15f)/8.0f;
const vec3 C21  = vec3(-.06f,-.05f,-.04f)/8.0f;
const vec3 C22  = vec3( .02f, .00f,-.05f)/8.0f;

void main() {

	vec3 Norm = normalize(fragNorm);
	vec3 Tan = normalize(fragTan.xyz - Norm * dot(fragTan.xyz, Norm));
	vec3 Bitan = cross(Norm, Tan) * fragTan.w;
	mat3 tbn = mat3(Tan, Bitan, Norm);
	vec4 nMap = texture(normMap, fragUV);
	vec3 N = normalize(tbn * (nMap.rgb * 2.0 - 1.0));

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
	vec3 Lambert = MD * clamp(dot(lightDir, N), 0, 1);
	vec3 H = normalize(lightDir + V);
	vec3 Blinn = MS * pow(clamp(dot(N, H), 0, 1), gamma);

	// Ambient light using Spherical Harmonics
	vec3 SphericalHarmonics = MA * (
		C00
		+ N.x * C1m1
		+ N.z * N.x * C10
		+ N.y * C11
		+ N.y * N.z * C2m2
		+ N.z * C2m1
		+ N.x * N.y * C21
		+ (pow(N.x, 2) - pow(N.y, 2)) * C22
		+ (3 * pow(N.z, 2) - 1) * C20);
	
	// Add all components
	outColor = vec4(
		clamp(
			(Lambert	// Diffusion Model
				+ Blinn) // Specular Model
			* PointLight // Only Diffusion and Specular depends on light model
			+ SphericalHarmonics // Ambient light model
			+ ME,	// Emission component only depends on the emission of the object
			0, 1),
		1.0f);	// output color
}

