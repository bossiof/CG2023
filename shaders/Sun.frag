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

float time = sin(gubo.time);


void main() {
	// outputColor only depends on the texture itself
//	outColor = texture(tex, fragUV);
	outColor = clamp((0.1+abs(time)),0.0,1.0)* texture(tex, fragUV);

}
