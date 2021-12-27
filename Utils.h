#pragma once
#include <vector>
#include <iostream>
#include <vulkan.h>
#include "Common.h"

namespace Utils {
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
};