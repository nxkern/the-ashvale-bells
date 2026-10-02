#include <raylib.h>

#include "animation.h"
#include "player.h"

Player::Player(float x, float y) : x(x), y(y) {
  _animation_idle_east =
      CreateSpriteAnimation("resources/sprites/characters/wrenn/Idle/"
                            "animations/Fight_Stance_Idle/east/",
                            3, 8, 68, 68);
  _animation_idle_west =
      CreateSpriteAnimation("resources/sprites/characters/wrenn/Idle/"
                            "animations/Fight_Stance_Idle/west",
                            3, 8, 68, 68);
}

void Player::move(float dx, float dy) {
  x += dx;
  y += dy;

  float max_x = GetScreenWidth() - _animation_idle_east.atlas.width;
  float max_y = GetScreenHeight() - _animation_idle_east.atlas.height;
  if (x < 0)
    x = 0;
  if (x > max_x)
    x = max_x;
  if (y < 0)
    y = 0;
  if (y > max_y)
    y = max_y;
}

void Player::draw(std::string action) const {
  if (action == "idle_east")
    DrawPlayerAnimationPro(_animation_idle_east,
                           {(float)x, (float)y, 68.0f, 68.0f}, {0.0f, 0.0f},
                           0.0f, WHITE);
  if (action == "idle_west")
    DrawPlayerAnimationPro(_animation_idle_west,
                           {(float)x, (float)y, 68.0f, 68.0f}, {0.0f, 0.0f},
                           0.0f, WHITE);
}
