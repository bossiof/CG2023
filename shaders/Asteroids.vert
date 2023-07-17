#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 1, binding = 0) uniform UniformBufferObject {
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inTan;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragUV;
layout(location = 3) out vec4 fragTan;

void main() {
    gl_Position = ubo.mvpMat * vec4(inPos, 1.0);
    fragPos = (ubo.mMat * vec4(inPos, 1.0)).xyz;
    fragNorm = mat3(ubo.nMat[0].xyz, ubo.nMat[1].xyz, ubo.nMat[2].xyz) * inNorm;
    fragTan = vec4(mat3(ubo.nMat[0].xyz, ubo.nMat[1].xyz, ubo.nMat[2].xyz) * inTan.xyz, inTan.w);
    fragUV = inUV;
}