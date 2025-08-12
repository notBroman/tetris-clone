#include <iostream>
#include <queue>
#include "renderer.hpp"
#include <GLFW/glfw3.h>

enum State {MENU=0, GAMEPLAY, END};

enum Event {LEFT=0, RIGHT, UP, DOWN, PAUSE, STOP};

class App{
private:
  Renderer* renderer;
  State state;
  std::queue<Event> eventQueue;
  bool close_window = false;
public:
  App(){
    renderer = new Renderer;
    state = MENU;
  };

  void run(){

    pollInput();

    switch(state){
      case MENU:
      default:
	break;
    }
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
