#ifndef _ARENA_HPP
#define _ARENA_HPP

#include <stdint.h>

class Arena{
private:
  uint32_t size_x, size_y;
public:
  Arena();
  ~Arena();
};

#endif
