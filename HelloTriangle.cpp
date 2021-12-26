#include <vulkan.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "./include/GLFW/glfw3.h"
#include "./include/glm/vec4.hpp"
#include "./include/glm/mat4x4.hpp"
#define GLFW_INCLUDE_VULKAN

#include "Validator.cpp"
#include "Utils.cpp"
#include "Common.h"

class HelloTriangleApplication {
public:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    const std::vector<char*> validationLayersRequested = 
        { "VK_LAYER_KHRONOS_validation" };

    void run() {
        initWindow();
        createInstance();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;
    VkResult result;
    VkDebugUtilsMessengerEXT debugMessenger;

    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void createInstance() {
        if (enableValidationLayers && 
            !Validator::checkValidationLayerSupport(validationLayersRequested)) {
            throw std::runtime_error(
                "validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
            nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
            extensions.data());
        std::cout << extensionCount << " extensions supported:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }

        auto glfwExtensions = Validator::getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
        createInfo.ppEnabledExtensionNames = glfwExtensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = 
                static_cast<uint32_t>(validationLayersRequested.size());
            createInfo.ppEnabledLayerNames = validationLayersRequested.data();

            Utils::populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)
                &debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            Validator::handleCreateInstanceFailure(result);
            throw std::runtime_error("failed to create instance!");
        }

        Utils::setupDebugMessenger(instance, debugMessenger);
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        if (enableValidationLayers) {
            Utils::DestroyDebugUtilsMessengerEXT(instance, 
                debugMessenger, nullptr);
        }

        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};