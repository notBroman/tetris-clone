FetchContent_Declare(
	VulkanMemoryAllocator
	GIT_REPOSITORY 	https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git
	GIT_TAG 	1d8f600fd424278486eade7ed3e877c99f0846b1 #v3.3.0
	FIND_PACKAGE_ARGS
)

FetchContent_Declare(
	vk-bootstrap
	GIT_REPOSITORY 	https://github.com/charles-lunarg/vk-bootstrap.git
	GIT_TAG		7028d6f652fdca9da332b4b4df25860ae19302fb #v1.4.336
	FIND_PACKAGE_ARGS
)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY	https://github.com/ocornut/imgui.git
	GIT_TAG		6d910d5487d11ca567b61c7824b0c78c569d62f0
	FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(
	VulkanMemoryAllocator
	vk-bootstrap
	imgui
)

find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(vk-bootstrap CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(renderer renderer.cpp)
add_library(stb INTERFACE stb_image.h)

target_link_libraries(renderer PRIVATE stb)
target_link_libraries(renderer PRIVATE glfw)
target_link_libraries(renderer PRIVATE Vulkan::Vulkan)
target_link_libraries(renderer PUBLIC glm::glm)
target_link_libraries(renderer PRIVATE vk-bootstrap)
target_link_libraries(renderer PRIVATE GPUOpen::VulkanMemoryAllocator)
target_link_directories(renderer PUBLIC  ${imgui_DIR})
