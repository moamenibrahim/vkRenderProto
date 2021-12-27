#include "HelloTriangle.h"
#include <numeric>
#include <iostream>

class HelloTriangleApplication 
{
public:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    const std::vector<char *> validationLayersRequested = 
        { "VK_LAYER_KHRONOS_validation" };

    void run() 
    {
        initWindow();
        createInstance();
        pickPhysicalDevice();
        createLogicalDevice();
        mainLoop();
        cleanup();
    }

private:
    VkPhysicalDevice physicalDevice{};
    VkDevice device;
    GLFWwindow* window;
    VkInstance instance;
    VkResult result;
    VkDebugUtilsMessengerEXT debugMessenger;

    void initWindow() 
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void createInstance() 
    {
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
        else 
        {
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

    void pickPhysicalDevice() 
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) 
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (Utils::isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) 
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        // Use an ordered map to automatically sort candidates by score
        std::multimap<int, VkPhysicalDevice> candidates;
        
        for (const auto& device : devices) 
        {
            int score = Utils::rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if (candidates.rbegin()->first > 0) 
        {
            physicalDevice = candidates.rbegin()->second;
        }
        else 
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    void createLogicalDevice() {
        Utils::QueueFamilyIndices indices = Utils::findQueueFamilies(physicalDevice);
        
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayersRequested.size());
            createInfo.ppEnabledLayerNames = validationLayersRequested.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

    }

    void mainLoop() 
    {
        while (!glfwWindowShouldClose(window)) 
        {
            glfwPollEvents();
        }
    }

    void cleanup() 
    {
        vkDestroyDevice(device, nullptr);
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        if (enableValidationLayers) {
            Utils::DestroyDebugUtilsMessengerEXT(instance, 
                debugMessenger, nullptr);
        }

        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};