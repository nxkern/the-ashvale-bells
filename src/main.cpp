#include <raylib.h>
#include <string>

#include "entities/player/player.h"
#include "utils/config.h"

void drawing(Player jugador, std::string action);

auto main() -> int {

  InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
             "The Ashvale Bells");
  SetTargetFPS(60);

  Player jugador(100.0f, 100.0f);
  std::string action = "idle_east";

  while (WindowShouldClose() == false) {
    if (IsKeyDown(KEY_RIGHT)) {
      jugador.move(200.0f * GetFrameTime(), 0);
      action = "idle_east";
    }
    if (IsKeyDown(KEY_LEFT)) {
      jugador.move(-200.0f * GetFrameTime(), 0);
      action = "idle_west";
    }
    if (IsKeyDown(KEY_UP))
      jugador.move(0, -200.0f * GetFrameTime());
    if (IsKeyDown(KEY_DOWN))
      jugador.move(0, 200.0f * GetFrameTime());
    drawing(jugador, action);
  }

  CloseWindow();
  return 0;
}

void drawing(Player jugador, std::string action) {

  BeginDrawing();
  ClearBackground(RAYWHITE);
  jugador.draw(action);
  EndDrawing();
}
