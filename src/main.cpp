#include <iostream>
#include <queue>
#include "renderer.hpp"

enum State {MENU=0, GAMEPLAY, END};

enum Event {LEFT=0, RIGHT, UP, DOWN, PAUSE, STOP};

class App{
private:
  Renderer renderer;
  State state;
  std::queue<Event> eventQueue;
public:
  App(){
    renderer = Renderer();
    state = MENU;
  };

private:
  void pollInput();

  void run(){

    pollInput();

    switch(state){
      case MENU:
	std::cout << "Menu Screen" << std::endl;
      default:
	break;
    }
  }
private:

};

int main(){
  std::cout << "Tetris" << std::endl;
  App app = App();
  while (true) {
    app.run();
  }
}
