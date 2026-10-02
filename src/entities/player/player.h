#pragma once

#include <raylib.h>

#include "animation.h"

class Player {
public:
  Player(float x, float y);
  ~Player();

  void move(float dx);
  void jump();
  void update(float delta_time);
  void draw(std::string action) const;

  void collisionWithFloor(float floorY);
  Vector2 getPosition();
  bool is_on_ground;

protected:
  // pos
  Vector2 position;
  
  // stats
  Vector2 velocity;
  float scale_jump = 3.0f;

  // animations
  PlayerAnimation _animation_idle_east;
  PlayerAnimation _animation_idle_west;
  PlayerAnimation _animation_running_east;
  PlayerAnimation _animation_running_west;
  PlayerAnimation _animation_jump_east;
  PlayerAnimation _animation_jump_west;
};
