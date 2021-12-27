#include <vector>
#include <iostream>
#include <vulkan.h>

#include "./include/GLFW/glfw3.h"
#include "vk_enum_string_helper.h"
#include "Common.h"

class Validator {
public:
	static bool checkValidationLayerSupport(std::vector<char*> &validationLayers) {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount,
			availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;	
				}
			}
			if (!layerFound) {
				return false;
			}
		}
		return true;
	}

	static void handleCreateInstanceFailure(VkResult result) {
		std::cout << "Error on creating instance: " << 
			string_VkResult(result) << "\n";
	}

	static std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions =
			glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions,
			glfwExtensions + glfwExtensionCount);
			
		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return extensions;
	}
};