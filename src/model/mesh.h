#pragma once
#include "../include/glm/glm.hpp"
#include "../include/glm/common.hpp"
//#include "vk_types.h"
#include <vector>
struct Vertex 
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};
class Mesh
{
public:
	Mesh(const std::vector<glm::vec3> positions, const std::vector<glm::vec3> normals, const std::vector<glm::vec3> colors, const std::vector<uint32_t> indices);

	Mesh(const Mesh& m) { vertices_ = m.vertices_; indices_ = m.indices_; }
	Mesh& operator=(const Mesh& t) { return *this; }
	bool HasIndices() { return !indices_.empty(); }
	const std::vector<Vertex> GetVertices() { return vertices_; }
	const std::vector<uint32_t> GetIndices() { return indices_; }

private:

	std::vector<Vertex> vertices_;
	std::vector<uint32_t> indices_;
	//AllocatedBuffer _vertexBuffer; //TODO: Placeholder

};