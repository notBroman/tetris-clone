#include <iostream>
#include <queue>
#include "block/block.hpp"
#include "arena/arena.hpp"
#include "renderer/renderer.hpp"
#include <GLFW/glfw3.h>

enum State {MENU=0, GAMEPLAY, END};

enum Event {LEFT=0, RIGHT, UP, DOWN, PAUSE, STOP};

class App{
private:
  Renderer* renderer;
  State state;
  std::queue<Event> eventQueue;
  bool close_window = false;
  Arena arena;
  GLFWwindow* window;
public:
  App(){
    std::cout << "App creation" << std::endl;
    state = MENU;
    renderer = new Renderer();
    arena = Arena();
  };

  ~App(){
    std::cout << "App deletion" << std::endl;
    renderer->~Renderer();
    arena.~Arena();
  }

  void run(){

    /*
    * Main game loop:
    *
    * 1. collect the inputs
    * 2. update the game state based on inputs and current state
    * 3. render the game state to screen
    */
    window = renderer->getWindow();
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
      switch(state){
	case MENU:
	  break;
	case GAMEPLAY:
	  break;
	default:
	  break;
      }

      renderer->draw();
    }
  }

};

int main(){
  std::cout << "Tetris" << std::endl;
  App app = App();
  app.run();
}
