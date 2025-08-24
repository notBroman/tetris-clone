#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <cstddef>
#include <cstdint>
#include <ios>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <set>
#include <vector>
#include <optional>
#include <array>
#include <fstream>

struct Vertex{
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 texCoord;

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::array<VkVertexInputAttributeDescription, 3> getAtrributeDescription() {
    std::array<VkVertexInputAttributeDescription, 3> attributeDescription{};

    attributeDescription[0].binding = 0;
    attributeDescription[0].location = 0;
    attributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescription[0].offset = offsetof(Vertex, pos);

    attributeDescription[1].binding = 0;
    attributeDescription[1].location = 1;
    attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescription[1].offset = offsetof(Vertex, color);

    attributeDescription[2].binding = 0;
    attributeDescription[2].location = 2;
    attributeDescription[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescription[2].offset = offsetof(Vertex, texCoord);

    return attributeDescription;
  }
};

struct UniformBufferObject{
  alignas(16) glm::mat4 model;
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 proj;
};

const std::vector<Vertex> vertices = {
  {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
  {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
  {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
  {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

  {{-0.25f, -0.25f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
  {{0.25f, -0.25f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
  {{0.25f, 0.25f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
  {{-0.25f, 0.25f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<uint16_t> indices ={
  0, 1, 2, 2, 3, 0,
  4, 5, 6, 6, 7, 4
};

const int MAX_FRAMES_IN_FLIGHT = 2;

// function to load vkCreateDebugUtilsMessengerEXT
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, 
                                       const VkAllocationCallbacks* pAllocator);

static std::vector<char> readFile(const std::string& filename){
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  // can't find the file... don't know why

  if(!file.is_open()){
    throw std::runtime_error("failed to open file!");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();
  return buffer;
}

class Renderer {
private:
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

  std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
  };

  #ifdef NDEBUG
    const bool enableValidationLayers = false;
  #else
    const bool enableValidationLayers = true;
  #endif

  GLFWwindow *window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData){

    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
    }

    return VK_FALSE;
  }

  VkSurfaceKHR surface;
  VkQueue presentQueue;
  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;

  struct QueueFamilyIndices{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete(){
      return graphicsFamily.has_value() && presentFamily.has_value();
    }
  };
  
  struct SwapChainSupportDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

  VkRenderPass renderPass;
  VkPipeline graphicsPipeline;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;


  std::vector<VkFramebuffer> swapChainFrambuffers;

  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;
  std::vector<void*> uniformBuffersMapped;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;

  VkImage depthImage;
  VkDeviceMemory depthImageMemory;
  VkImageView depthImageView;

  VkDeviceMemory indexBufferMemory;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;

  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSet;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  uint32_t currentFrame = 0;

  bool framebufferResized = false;

public:
  void run();
  GLFWwindow* getWindow();
  void mainLoop();
  void drawFrame();
  Renderer();
  ~Renderer();
  void draw();
private:
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
  void setupDebugMessenger();
  std::vector<const char*> getRequiredExtensions();
  void initWindow();
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height){
    auto app = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
  }
  void initVulkan();
  void createDescriptorSetLayout();
  void createDescriptorPool();

  void createDescriptorSet();
  void createSurface();
  
  void createInstance();
  bool checkValidationSupport();
  void pickPhysicalDevice();
  void cleanup();
  bool isDeviceSuitable(VkPhysicalDevice device);

  bool checkDeviceExtensionSupport(VkPhysicalDevice physical_device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  void createLogicalDevice();
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physical_device);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  void createSwapChain();
  void createImageViews();
  void createGraphicsPipeline();
  VkShaderModule createShaderModule(const std::vector<char>& code);
  void createRenderPass();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffers();
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  void createSyncObjects();
  void updateUniformBuffer(uint32_t currentImage);
  void createUniformBuffers();

  void createIndexBuffer();
  void createVertexBuffer();
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void cleanupSwapChain();
  void recreateSwapChain();
  void createTextureImage();
  void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  VkCommandBuffer beginSingleTimeCommands();

  void endSingleTimeCommandBuffer(VkCommandBuffer commandBuffer);
  VkCommandBuffer setupCommandBuffer(); 
  void flushSetupCommandBuffer(VkCommandBuffer commandBuffer);
  void transitionImageLayout(VkCommandBuffer commandBuffer, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
  void copyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
  void createTextureImageView();
  VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
  void createImageSampler();
  void createDepthResources();
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);

};
#endif
