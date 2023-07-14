#ifndef MESH_GENERATE_HPP
#define MESH_GENERATE_HPP

#include <data_types.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <vector>

void createSphereMesh(
    std::vector<VertexNormUV> &vDef,
    std::vector<uint32_t> &vIdx);

#endif//MESH_GENERATE_HPP