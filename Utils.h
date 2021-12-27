#pragma once
#include <vector>
#include <iostream>
#include <vulkan.h>
#include <optional>
#include "EngineCommon.h"

namespace Utils {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() &&
				presentFamily.has_value();
		}
	};

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT &messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT &messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	void setupDebugMessenger(const VkInstance &instance,
		VkDebugUtilsMessengerEXT &debugMessenger);

	VkResult CreateDebugUtilsMessengerEXT(const VkInstance &instance,
		VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT*
		pDebugMessenger);
		
	void DestroyDebugUtilsMessengerEXT(const VkInstance &instance,
		VkDebugUtilsMessengerEXT &debugMessenger, const
		VkAllocationCallbacks* pAllocator);

	void populateDebugMessengerCreateInfo(
		VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	bool isDeviceSuitable(const VkPhysicalDevice &device, VkSurfaceKHR surface);

	int rateDeviceSuitability(const VkPhysicalDevice &device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
};