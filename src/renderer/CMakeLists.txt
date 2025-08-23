add_library(renderer renderer.cpp)
add_library(vk-bootstrap VkBootstrap.cpp)

target_include_directories(renderer SYSTEM PRIVATE "${stb_DIR}")
target_link_libraries(renderer PRIVATE glfw)
target_link_libraries(renderer PRIVATE Vulkan::Vulkan)
target_link_libraries(renderer PUBLIC glm::glm)
target_link_libraries(renderer PRIVATE vk-bootstrap)
