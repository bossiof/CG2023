#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject{
	mat4 mvpMat;
	mat4 mMat;
	float time;
} gubo;

layout(set = 0, binding = 1) uniform sampler2D tex;

float iTime = pow(sin(gubo.time/4),2);
vec2 iResolution = vec2(800,600); 


void main() {
	// outputColor only depends on the texture itself
	//outColor = texture(tex, fragUV);
	outColor.r = (0.8+0.2*iTime)*texture(tex, fragUV).r;
	outColor.g = (0.8+0.2*iTime)*(1-clamp(0.38*(0.7+iTime),0.0,1.3))* texture(tex, fragUV).g;
	outColor.b = (0.8+0.2*iTime)*(1-clamp(0.38*(0.7+iTime),0.0,1.3))*texture(tex, fragUV).b;
	outColor[3]=  texture(tex, fragUV)[3];
}