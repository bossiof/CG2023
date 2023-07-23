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
	alignas(16) glm::vec3 eyePos;
};

struct PlainUniformBlock {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(4)  float time;
};
struct TextUniformBlock {
	alignas(4) float visible;
};

// Define vertext types

// Only contains position and UV
struct VertexUV {
	glm::vec3 pos;
	glm::vec2 UV;
};

// Also contains normals
struct VertexNormUV {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

struct VertexTorus {
	glm::vec3 pos;
	glm::vec2 UV;
	glm::vec3 norm;
	glm::vec3 tan;
};
struct VertexEarth {
	glm::vec3 pos;
	glm::vec2 UV;
	glm::vec3 norm;
};

struct VertexNormTanUV {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
	glm::vec4 tan;
};

struct VertexNorm {
	glm::vec3 pos;
	glm::vec3 norm;
};

struct VertexText {
	glm::vec2 pos;
	glm::vec2 UV;
};

#endif//VERTEX_TYPES_HPP