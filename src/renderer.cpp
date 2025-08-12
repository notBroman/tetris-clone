#include "renderer.hpp"

Renderer::Renderer(){
  initWindow();
  initVulkan();
}

Renderer::~Renderer(){
  cleanup();
}

void Renderer::initWindow(){
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "tetris clone", nullptr, nullptr);
}

void Renderer::initVulkan(){
  vkb::InstanceBuilder builder;
    auto inst_ret =
        builder.set_app_name("Tetris clone").request_validation_layers().use_default_debug_messenger().build();
    if (!inst_ret) {
        std::cerr << "Failed to create Vulkan instance. Error: " << inst_ret.error().message() << "\n";
    }
    vkb_inst = inst_ret.value();
}

void Renderer::cleanup(){

  glfwDestroyWindow(window);

  glfwTerminate();
}

