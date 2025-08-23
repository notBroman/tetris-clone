add_library(renderer renderer.cpp)
add_library(vk-bootstrap VkBootstrap.cpp)
add_library(stb INTERFACE stb_image.h)

target_link_libraries(renderer PRIVATE stb)
target_link_libraries(renderer PRIVATE glfw)
target_link_libraries(renderer PRIVATE Vulkan::Vulkan)
target_link_libraries(renderer PUBLIC glm::glm)
target_link_libraries(renderer PRIVATE vk-bootstrap)
