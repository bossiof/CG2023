#ifndef VERTEX_TYPES_HPP
#define VERTEX_TYPES_HPP

#include <glm/glm.hpp>

struct MeshUniformBlock {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

struct GlobalUniformBlockPointLight {
	alignas(16) glm::vec3 lightPos;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 AmbLightColor;
	alignas(16) glm::vec3 eyePos;
};

struct PlainUniformBlock {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
};

struct VertexUV {
	glm::vec3 pos;
	glm::vec2 UV;
};

// The vertices data structures
struct VertexNormUV {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

#endif//VERTEX_TYPES_HPP