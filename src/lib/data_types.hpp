#ifndef VERTEX_TYPES_HPP
#define VERTEX_TYPES_HPP

#include <glm/glm.hpp>

struct UniformBufferObject {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

struct GlobalUniformBufferObject {
	alignas(16) glm::vec3 lightDir;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 eyePos;
};

struct VertexUV {
	glm::vec3 pos;
	glm::vec2 UV;
};

struct PlainUniformBlock {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
};

// The vertices data structures
struct VertexNormUV {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

#endif//VERTEX_TYPES_HPP