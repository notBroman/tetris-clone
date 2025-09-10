#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <stdint.h>
#include "block.hpp"
#include "arena.hpp"

typedef struct GameState{
  std::vector<Block> pieces;
} GameState;

class Game{
public:
  GameState* getState();
};

#endif
