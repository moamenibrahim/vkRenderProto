cmake_minimum_required(VERSION 3.15)
project(VKRendererProto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




#set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/include/spdlog/")
#target_include_directories(VKRendererProto PUBLIC ${SPDLOG_DIR})
add_executable(VKRendererProto main.cpp "Engine.cpp" "Utils.cpp" "Validator.cpp")

target_include_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/include/GLFW/")
target_link_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/include/GLFW/lib")
target_link_libraries(VKRendererProto glfw3)
target_include_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/include/vulkan/")
target_link_directories(VKRendererProto PUBLIC "C:/VulkanSDK/1.2.189.2/Lib/")
target_link_libraries(VKRendererProto vulkan-1)

