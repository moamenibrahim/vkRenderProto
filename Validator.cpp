#include <vector>
#include <iostream>
#include <vulkan.h>
#include <map>

#include "vk_enum_string_helper.h"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class Validator {
public:
	static bool checkValidationLayerSupport(std::vector<char*> validationLayers) {
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

	static void handleInstanceCreateFailure(VkResult result) {
		
		std::cout << "Error on creating instance: " << string_VkResult(result) << "\n";
	}
};