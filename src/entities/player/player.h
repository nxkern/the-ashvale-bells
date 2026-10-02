#pragma once

#include <raylib.h>

#include "animation.h"

class Player {
public:
  Player(float x, float y);

  void move(float dx, float dy);
  void draw(std::string action) const;

protected:
  float x;
  float y;
  PlayerAnimation _animation_idle_east;
  PlayerAnimation _animation_idle_west;
};
