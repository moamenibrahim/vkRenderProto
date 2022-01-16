cmake_minimum_required(VERSION 3.15)
project(VKRendererProto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/include/spdlog/")
#target_include_directories(VKRendererProto PUBLIC ${SPDLOG_DIR})
add_executable(VKRendererProto src/main.cpp "src/Engine.cpp" "src/Utils.cpp" "src/Validator.cpp" "src/HelloTriangle.cpp" "src/model/mesh.cpp" "src/model/model.cpp" "src/model/mesh_manager.cpp" "src/model/model_manager.cpp")

target_include_directories(VKRendererProto PUBLIC ${CMAKE_SOURCE_DIR}/src/include/GLFW/)
target_include_directories(VKRendererProto PUBLIC ${CMAKE_SOURCE_DIR}/src/include/glm/)
target_include_directories(VKRendererProto PUBLIC ${CMAKE_SOURCE_DIR}/src/include/vulkan/)

if(NOT WIN32)
    target_link_directories(VKRendererProto PUBLIC ${CMAKE_SOURCE_DIR}/vulkan/1.2.198.1/x86_64/lib/)
    target_link_libraries(VKRendererProto PUBLIC vulkan ${CMAKE_DL_LIBS})
    
    find_package(glfw3 REQUIRED)
    target_link_libraries(VKRendererProto PUBLIC glfw3 ${CMAKE_DL_LIBS})
else()
    target_link_libraries(VKRendererProto PUBLIC glfw3)

    target_link_directories(VKRendererProto PUBLIC "C:/VulkanSDK/1.2.189.2/Lib/")
    target_link_libraries(VKRendererProto PUBLIC vulkan-1)
endif()

enable_testing()
add_test(NAME Runs COMMAND VKRendererProto)

# Remote machine does not provide full vulkan support so errors occur when running
set_tests_properties(Runs PROPERTIES PASS_REGULAR_EXPRESSION "failed to create instance!")
