#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 1, binding = 0) uniform UniformBufferObject {
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNorm;

void main() {
    gl_Position = ubo.mvpMat * vec4(inPos, 1.0);
    fragPos = (ubo.mMat * vec4(inPos, 1.0)).xyz;
    fragNorm = mat3(ubo.nMat[0].xyz, ubo.nMat[1].xyz, ubo.nMat[2].xyz) * inNorm;
}