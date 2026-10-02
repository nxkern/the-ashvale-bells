#include <raylib.h>
#include <string>

#include "entities/player/player.h"
#include "utils/config.h"

void drawing(const Player &jugador, std::string action);
void controllerPlayer(Player &jugador, std::string *action);

auto main() -> int {

  InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "The Ashvale Bells");
  SetTargetFPS(120);

  Player jugador(100.0f, 100.0f);
  std::string action = "idle_east";
  float floorY = 500.0f;

  while (WindowShouldClose() == false) {
    controllerPlayer(jugador, &action);
    jugador.update(GetFrameTime());
    if (jugador.getPosition().y + 68.0f > floorY) {
      jugador.collisionWithFloor(floorY);
      if (action == "jump_east")
        action = "idle_east";
      if (action == "jump_west")
        action = "idle_west";
      jugador.is_on_ground = true;
    }
    drawing(jugador, action);
  }

  CloseWindow();
  return 0;
}

void drawing(const Player &jugador, std::string action) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  jugador.draw(action);
  EndDrawing();
}

void controllerPlayer(Player &jugador, std::string *action) {
  if (IsKeyDown(KEY_RIGHT)) {
    jugador.move(200.0f * GetFrameTime());
    if (jugador.is_on_ground) {
      *action = "running_east";
    } else {
        *action = "jump_east";
    }
  } else if (IsKeyDown(KEY_LEFT)) {
    jugador.move(-200.0f * GetFrameTime());
    if (jugador.is_on_ground) {
      *action = "running_west";
    } else {
        *action = "jump_west";
    }
  } else {
    if (*action == "running_east")
      *action = "idle_east";
    if (*action == "running_west")
      *action = "idle_west";
  }
  if (IsKeyPressed(KEY_SPACE) && jugador.is_on_ground) {
    jugador.jump();
    if (*action == "idle_east" || *action == "running_east") {
      *action = "jump_east";
    }
    if (*action == "idle_west" || *action == "running_west") {
      *action = "jump_west";
    }
    jugador.is_on_ground = false;
  }
}
