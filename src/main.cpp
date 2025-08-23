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
public:
  App(){
    state = MENU;
    renderer = new Renderer;
    arena = Arena();
  };

  ~App(){
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
    while(!close_window){
      switch(state){
	case MENU:
	  if(glfwGetKey(renderer->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
	    close_window = true;
	  }
	  break;
	case GAMEPLAY:
	  break;
	default:
	  break;
      }

      renderer->run();
    }
  }

};

int main(){
  std::cout << "Tetris" << std::endl;
  App app = App();
  app.run();
}
