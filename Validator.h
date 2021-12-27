#pragma once
#include <vector>
#include <iostream>
#include <vulkan.h>

#include "./include/GLFW/glfw3.h"
#include "vk_enum_string_helper.h"
#include "Common.h"
//#include "include/spdlog/spdlog.h"

namespace Validator 
{
	bool checkValidationLayerSupport(const std::vector<std::string>& validationLayers);
	void handleCreateInstanceFailure(const VkResult &result);
	std::vector<const char*> getRequiredExtensions();
};