#ifndef _RENDERER_HPP
#define _RENDERER_HPP

class Renderer{
private:

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
