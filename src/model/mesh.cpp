#include "mesh.h"

Mesh::Mesh(const std::vector<glm::vec3> positions, const std::vector<glm::vec3> normals, const std::vector<glm::vec3> colors, const std::vector<uint32_t> indices)
{
	for (size_t k = 0; k < positions.size(); k++)
	{
		auto& new_vertex = vertices_.emplace_back();
		new_vertex.position = positions[k];
		new_vertex.normal = normals[k];
		new_vertex.color = colors[k];
	}
	indices_ = indices;
}

