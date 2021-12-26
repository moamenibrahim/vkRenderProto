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

class HelloTriangleApplication {
public:
    GLFWwindow* window;
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
    VkInstance instance;
    VkResult result;

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
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = 
                static_cast<uint32_t>(validationLayersRequested.size());
            createInfo.ppEnabledLayerNames = validationLayersRequested.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount,
            nullptr);
        std::cout << glfwExtensionCount << " extensions supported\n";

        std::vector<VkExtensionProperties> glfwExtensions(glfwExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount,
            glfwExtensions.data());

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = 
            glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            Validator::handleInstanceCreateFailure(result);
            throw std::runtime_error("failed to create instance!");
        }

        if (&createInfo == nullptr || instance == nullptr) {
            std::cout << "Null pointer passed to required parameter!";
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};