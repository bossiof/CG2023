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
//we create an internal time varying betweeen 0 and 1
float iTime = pow(sin(gubo.time/6),2);

void main() {
	//the sun output color is based only on the texture and decreases and increases slightly with time
	outColor.r = 0.02+(0.6+0.5*iTime)*texture(tex, fragUV).r;
	outColor.g = 0.02+(0.8+0.5*iTime)* texture(tex, fragUV).g;
	outColor.b = 0.02+(0.6+0.4*iTime)*texture(tex, fragUV).b;
	outColor[3]=  texture(tex, fragUV)[3];
}