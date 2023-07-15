#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform UniverseUniformBufferObject {
	mat4 mvpMat;
	mat4 mMat;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUV;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec2 fragUV;

void main() {
	// Apply ViewProjectionMatrix
	gl_Position = ubo.mvpMat * vec4(inPosition, 1.0);
	// Applay matrix for determine fragment position
	fragPos = (ubo.mMat * vec4(inPosition, 1.0)).xyz;
	// Just forward UV mapping
	fragUV = inUV;
}