#version 450

layout(binding = 0) uniform UniformBufferObject {
	float visible;
} ubo;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inUV;

layout(location = 0) out vec2 outUV;

void main() {
	gl_Position = vec4(inPosition * ubo.visible, 0.5f, 1.0f);
	outUV = inUV;
}