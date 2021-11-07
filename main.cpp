#include "./include/vulkan/vulkan.h"
//#define GLFW_INCLUDE_VULKAN

#include "./include/GLFW/glfw3.h"
#include "./include/glm/vec4.hpp"
#include "./include/glm/mat4x4.hpp"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE


#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> cmd_arguments(argv, argv + argc);

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}