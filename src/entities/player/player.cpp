#include <cmath>
#include <raylib.h>

#include "../../utils/config.h"
#include "animation.h"
#include "player.h"

Player::Player(float x, float y) {
  position = Vector2{x, y};
  velocity = Vector2{0.0f, 0.0f};
  is_on_ground = true;

  _animation_idle_east =
      CreateSpriteAnimation("resources/sprites/characters/wrenn/Idle/"
                            "animations/Fight_Stance_Idle/east/",
                            8, 8, 68, 68);
  _animation_running_east = CreateSpriteAnimation(
      "resources/sprites/characters/wrenn/Idle/animations/Running/east/", 8, 8,
      68, 68);
  _animation_idle_west =
      CreateSpriteAnimation("resources/sprites/characters/wrenn/Idle/"
                            "animations/Fight_Stance_Idle/west",
                            8, 8, 68, 68);
  _animation_running_west = CreateSpriteAnimation(
      "resources/sprites/characters/wrenn/Idle/animations/Running/west/", 8, 8,
      68, 68);
  _animation_jump_east = CreateSpriteAnimation(
      "resources/sprites/characters/wrenn/Idle/animations/Jumping/east", 8, 8,
      68, 68);
  _animation_jump_west = CreateSpriteAnimation(
      "resources/sprites/characters/wrenn/Idle/animations/Jumping/west", 8, 8,
      68, 68);
}
Player::~Player() {
  DisposeSpriteAnimation(_animation_running_east);
  DisposeSpriteAnimation(_animation_running_west);
  DisposeSpriteAnimation(_animation_idle_east);
  DisposeSpriteAnimation(_animation_idle_west);
  DisposeSpriteAnimation(_animation_jump_west);
  DisposeSpriteAnimation(_animation_jump_east);
}

void Player::move(float dx) {
  position.x += dx;

  float max_x = GetScreenWidth() - 68.0f;
  if (position.x < 0)
    position.x = 0;
  if (position.x > max_x)
    position.x = max_x;
}
void Player::jump() {
  float force = scale_jump * 32.0f;
  velocity.y = -sqrtf(2.0f * Config::gravity * force);
}

void Player::update(float delta_time) {
  velocity.y += Config::gravity * delta_time;
  position.y += velocity.y * delta_time;
}

void Player::draw(std::string action) const {
  if (action == "idle_east")
    DrawPlayerAnimationPro(_animation_idle_east,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
  if (action == "idle_west")
    DrawPlayerAnimationPro(_animation_idle_west,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
  if (action == "running_east")
    DrawPlayerAnimationPro(_animation_running_east,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
  if (action == "running_west")
    DrawPlayerAnimationPro(_animation_running_west,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
  if (action == "jump_east")
    DrawPlayerAnimationPro(_animation_jump_east,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
  if (action == "jump_west")
    DrawPlayerAnimationPro(_animation_jump_west,
                           {(float)position.x, (float)position.y, 68.0f, 68.0f},
                           {0.0f, 0.0f}, 0.0f, WHITE);
}

void Player::collisionWithFloor(float floorY) {
  position.y = floorY - 68.0f;
  velocity.y = 0.0f;
};

Vector2 Player::getPosition() {
    return position;
}
