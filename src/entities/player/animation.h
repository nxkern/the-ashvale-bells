#pragma once

#include <raylib.h>
#include <string>

struct PlayerAnimation {
  Texture2D atlas;
  int frame_per_second;

  Rectangle *rectangles;
  int rectangles_lenght;
};

PlayerAnimation CreateSpriteAnimation(std::string route, int frame_per_second, int length, int frame_width, int frame_height);

void DisposeSpriteAnimation(PlayerAnimation animation);

Texture2D AnimationFrames(std::string route, int px_width, int px_height);

void DrawPlayerAnimationPro(PlayerAnimation animation, Rectangle dest,
                            Vector2 origin, float rotation, Color tint);
