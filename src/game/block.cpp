#include "block.hpp"

Block::Block(){
  shape = DOT;
  rotation = 0;
}

Block::~Block() = default;

void Block::rotate_cw(){
  /*
   * Rotate a block by 90 defrees clockwise
   * A block can be rotated 4 times to end up in the starting position
   */
  rotation = (rotation + 1)%4;
}

