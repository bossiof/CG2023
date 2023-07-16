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
layout(set = 1, binding = 2) uniform sampler2D norm;

const float beta = 0.1f;
const float g = 8;	

void main() {
	vec3 Norm = normalize((fragNorm+ texture(norm, fragUV).xyz) * 2.0 - 1.0);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	
	// replace the following lines with the code to implement a point light model
	// with the light color in gubo.lightColor, and the position in gubo.lightPos.
	// the exponent of the decay is in constant variable beta, and the base distance
	// is in constant g

	// Point light model: for the point model a position is needed to compute different
	// raylight direction and decay using the following formulas
	//   for the light directon: $\overrightarrow{lx}=\frac{p-x}{|p-x|}$
	//   and for the light decay: $L(l,\overrightarrow{lx})=(\frac{g}{|p-x|})^\beta l$
	//   with:
	//     l: the light color (and intensity)
	//     g: indicates te distance where the decay starts having effect
	//     beta: is the decay factor
	//     |p - x| is the distance between the light source and the fragment
	vec3 lightPos = gubo.lightPos;
	vec3 lightDir = normalize(gubo.lightPos - fragPos);
	vec3 lightColor = pow(g / distance(lightPos, fragPos), beta) * gubo.lightColor.xyz;

	vec3 Diffuse = texture(tex, fragUV).rgb * 0.99f * clamp(dot(Norm, lightDir),0.0,1.0);
	vec3 Specular = vec3(pow(clamp(dot(Norm, normalize(lightDir + EyeDir)),0.0,1.0), 160.0f));
	vec3 Ambient = texture(tex, fragUV).rgb * 0.2f;
	
	outColor = vec4(clamp((Diffuse + Specular) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}