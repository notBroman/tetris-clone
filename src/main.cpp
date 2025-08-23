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

    pollInput();

    switch(state){
      case MENU:
      default:
	break;
    }

    renderer->render();
  }

private:
  void pollInput(){
  };
};

int main(){
  std::cout << "Tetris" << std::endl;
  App app = App();
  while (true) {
    app.run();
  }
}
