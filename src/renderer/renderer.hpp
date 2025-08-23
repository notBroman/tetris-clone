#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "stb_image.h"
#include "VkBootstrap.h"
#include "VkBootstrapDispatch.h"

#include <glm/glm.hpp>
#include <stdexcept>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Renderer{
private:
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  GLFWwindow* window;
  vkb::Instance vkb_inst;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  vkb::Device vkb_device;
  VkDevice device;
  VkQueue graphics_queue;
  vkb::Swapchain vkb_swapchain;
  vkb::InstanceDispatchTable inst_disp;
  vkb::DispatchTable disp;

  std::vector<VkImage> swapchain_images;
  std::vector<VkImageView> swapchain_image_views;
  std::vector<VkFramebuffer> framebuffers;

  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> command_buffers;

  VkImage depthImage;
  VkDeviceMemory depthImageMemory;
  VkImageView depthImageView;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;

public:
  Renderer();
  ~Renderer();

  void render();

private:
  void initWindow();
  void initVulkan();

  void cleanup();

  void createRenderPass();
  void createGraphicsPipeline();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffers();
  void createSyncObjects();
  void drawFrame();
  VkShaderModule createShaderModule(vkb::DispatchTable disp, const std::vector<char>& code);

  static std::vector<char> readFile(const std::string& filename);

};

struct Vertex {
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

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

#endif
