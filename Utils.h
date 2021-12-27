#pragma once
#include <vector>
#include <iostream>
#include <vulkan.h>
#include <optional>
#include "Common.h"

namespace Utils {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		
		bool isComplete() {
			return graphicsFamily.has_value();
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

	bool isDeviceSuitable(const VkPhysicalDevice &device);

	int rateDeviceSuitability(const VkPhysicalDevice &device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};