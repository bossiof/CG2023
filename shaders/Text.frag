#version 450

layout(binding = 0) uniform UniformBufferObject {
	float visible;
} ubo;

layout(location = 0) in vec2 fragUV;
layout(location = 0) out vec4 outColor;
layout(binding = 1) uniform sampler2D tex;

void main() {
	outColor = vec4(texture(tex, fragUV).rgb, 1.0f);	// output color
}