#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 1, binding = 0) uniform UniverseUniformBufferObject {
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Norm;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec2 fragUV;
layout(location = 2) out vec3 fragNorm;

void main() {
	// Apply ViewProjectionMatrix
	gl_Position = ubo.mvpMat * vec4(Pos, 1.0);
	// Applay matrix for determine fragment position
	fragPos = (ubo.mMat * vec4(Pos, 1.0)).xyz;
	// Just forward UV mapping
	fragUV = UV;
	//Just pass out the Norm mapping
    fragNorm = mat3(ubo.nMat[0].xyz, ubo.nMat[1].xyz, ubo.nMat[2].xyz) * Norm;
}