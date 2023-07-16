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

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, float sigma) {

	float theta_i = pow(cos(dot(L,N)),-1);
	float theta_r = pow(cos(dot(V,N)),-1);
	float alpha   =	max(theta_i,theta_r);
	float beta	  =	min(theta_i,theta_r);
	float A		  = 1 - (0.5*(pow(sigma,2)/(pow(sigma,2)+0.33)));
	float B 	  = 0.45*(pow(sigma,2)/(pow(sigma,2)+0.09));
	vec3 vi		  = normalize(L-dot(L,N)*N);
	vec3 vr		  = normalize(V-dot(V,N)*N);
	float G 	  = max(0.0,dot(vi,vr));
	vec3 L_O_N    = Md*clamp(dot(L,N),0.0,1.0);
	vec3 Oren_Nayar = L_O_N*(A+(B*G*sin(alpha)*tan(beta)));
	return Oren_Nayar;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);

	vec3 lightDir = normalize(gubo.lightPos - fragPos);
	vec3 lightColor = gubo.lightColor.rgb;

	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, 1.1f);
	vec3 Ambient = texture(tex, fragUV).rgb * 0.15f;

	outColor = vec4(clamp(0.96 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}


