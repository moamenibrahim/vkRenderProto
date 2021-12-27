#pragma once
#include "../include/glm/glm.hpp"
#include <vector>
#include "model.h"


class Instance 
{
public:

	void Translate(glm::vec3 &translation) {};
	void Rotate(glm::vec3 &rotation_eulers) {};
	glm::mat4 GetTransform() { return glm::mat4(0.0); }

private:


};