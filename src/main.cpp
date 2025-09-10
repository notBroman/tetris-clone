#include <iostream>
#include <queue>
#include "game/game.hpp"
#include "renderer/renderer.hpp"
#include <GLFW/glfw3.h>

enum State {MENU=0, GAMEPLAY, END, QUIT};

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
    bool quit_pick_option = false;
    while (!glfwWindowShouldClose(window) && !close_window) {
      glfwPollEvents();
      switch(state){
	case MENU:
	  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
	    state = QUIT;
	  }
	  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
	    std::cerr << "UP" << std::endl;
	  }
	  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
	  }
	  if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
	  }
	  
	  break;
	case GAMEPLAY:
	  break;

	case QUIT:
	    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
	      quit_pick_option = false;
	      std::cerr << "Keep going?" << std::endl;
	    }
	    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
	      quit_pick_option = true;
	      std::cerr << "Close App?" << std::endl;
	    }
	    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
	      if (quit_pick_option){
		close_window = true;
	      } else{
		state = MENU;
	      }
	    }
	  break;
	default:
	  break;
      }

      renderer->draw(nullptr);
    }
  }

};

int main(){
  std::cout << "Tetris" << std::endl;
  App app = App();
  app.run();
}
