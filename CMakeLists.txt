cmake_minimum_required(VERSION 3.15)
project(VKRendererProto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/include/spdlog/")
#target_include_directories(VKRendererProto PUBLIC ${SPDLOG_DIR})
add_executable(VKRendererProto src/main.cpp "src/Engine.cpp" "src/Utils.cpp" "src/Validator.cpp" "src/HelloTriangle.cpp" "src/model/mesh.cpp" "src/model/model.cpp" "src/model/mesh_manager.cpp" "src/model/model_manager.cpp")

target_include_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/src/include/GLFW/")
target_include_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/src/include/glm/")

target_link_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/src/include/GLFW/lib")
target_link_libraries(VKRendererProto glfw3)
target_include_directories(VKRendererProto PUBLIC "${CMAKE_SOURCE_DIR}/src/include/vulkan/")
if(UNIX)
    target_link_directories(VKRendererProto PUBLIC "./vulkan/1.2.198.1/x86_64/lib/")
else()
    target_link_directories(VKRendererProto PUBLIC "C:/VulkanSDK/1.2.189.2/Lib/")
endif(UNIX)
target_link_libraries(VKRendererProto vulkan-1)
