#ifndef __BLOCK_HPP
#define __BLOCK_HPP

#include <stdint.h>

enum Shape{DOT=0, L, J, HAT, I};

class Block{
private:
  Shape shape;
  uint8_t rotation;
  uint8_t pos_x, pos_y;
public:
  Block();
  ~Block();
  void rotate_cw();
};

#endif
