#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "VkBootstrap.h"
#include <stdexcept>

#include <vector>
#include <iostream>

class Renderer{
private:
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  GLFWwindow* window;
  vkb::Instance vkb_inst;

public:
  Renderer();
  ~Renderer();

  void render();

private:
  void initWindow();
  void initVulkan();

  void cleanup();

};

#endif
