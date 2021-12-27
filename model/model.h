#pragma once
#include "../include/glm/glm.hpp"

#include "../include/tinygltf/tiny_gltf.h"
#include "../include/tinyobj/tiny_obj_loader.h"

#include <vector>

class Model
{
public:

private:
	std::vector<glm::vec3> vertices_;
	std::vector<uint32_t> indices_;
};