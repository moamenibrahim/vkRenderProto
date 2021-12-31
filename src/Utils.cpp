#include "Utils.h"


namespace Utils
{
	const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT &messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT &messageType,
		const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
		void *pUserData)
	{
		std::cerr << "validation layer: "
				  << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	void setupDebugMessenger(const VkInstance &instance,
							 VkDebugUtilsMessengerEXT &debugMessenger)
	{
		if (!enableValidationLayers)
			return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		Utils::populateDebugMessengerCreateInfo(createInfo);
		if (Utils::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
												&debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to set up debug messenger!");
		}
	}

	VkResult CreateDebugUtilsMessengerEXT(const VkInstance &instance,
										  VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
										  const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
			vkGetInstanceProcAddr(instance,
								  "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugUtilsMessengerEXT(const VkInstance &instance,
									   VkDebugUtilsMessengerEXT &debugMessenger, const VkAllocationCallbacks *pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
			vkGetInstanceProcAddr(instance,
								  "vkDestroyDebugUtilsMessengerEXT");
		if (func != VK_NULL_HANDLE)
		{

			func(instance, debugMessenger, pAllocator);
		}
	}

	void populateDebugMessengerCreateInfo(
		VkDebugUtilsMessengerCreateInfoEXT &createInfo)
	{
		createInfo = {};
		createInfo.sType =
			VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)debugCallback;
	}

	bool isDeviceSuitable(const VkPhysicalDevice &device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices = Utils::findQueueFamilies(device, surface);
		bool extensionsSupported = checkDeviceExtensionSupport(device);
		return indices.isComplete() && extensionsSupported;
	}

	int rateDeviceSuitability(const VkPhysicalDevice &device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		int score = 0;

		// Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType ==
			VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		// Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;

		// Application can't function without geometry shaders
		if (!deviceFeatures.geometryShader)
		{
			return 0;
		}
		return score;
	}

	QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device, const VkSurfaceKHR &surface)
	{
		QueueFamilyIndices indices;
		// Logic to find queue family indices to populate struct with

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
												 nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
												 queueFamilies.data());

		int i = 0;
		for (const auto &queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
												 &presentSupport);
			if (presentSupport)
			{
				indices.presentFamily = i;
			}
			i++;
		}
		return indices;
	}

	bool checkDeviceExtensionSupport(const VkPhysicalDevice &device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr,
											 &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr,
											 &extensionCount, availableExtensions.data());
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
		for (const auto &extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &
									capabilities,
								uint32_t WIDTH, uint32_t HEIGHT)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			VkExtent2D actualExtent = {WIDTH, HEIGHT};
			actualExtent.width =
				std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width,
																	 actualExtent.width));
			actualExtent.height =
				std::max(capabilities.minImageExtent.height,
						 std::min(capabilities.maxImageExtent.height,
								  actualExtent.height));
			return actualExtent;
		}
	}

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
	{
		for (const auto &availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device, const VkSurfaceKHR &surface)
	{
		SwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
												  &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
											 nullptr);
		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
												  &presentModeCount, nullptr);
		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
													  &presentModeCount, details.presentModes.data());
		}
		return details;
	}

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
	{
		for (const auto &availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
				availableFormat.colorSpace ==
					VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}
		std::cout << "\n available formats:" << availableFormats[0].format << std::endl;
		return availableFormats[0];
	}
};
