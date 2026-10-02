#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <raylib.h>
#include <string>
#include <vector>

#include "animation.h"

namespace fs = std::filesystem;

PlayerAnimation CreateSpriteAnimation(std::string route, int frame_per_second,
                                      int length, int frame_width,
                                      int frame_height) {

  Texture2D atlas = AnimationFrames(route, frame_width, frame_height);
  std::vector<Rectangle> rectangles;
  for (int i = 0; i < length; i++)
    rectangles.push_back(Rectangle{(float)(i * frame_width), 0.0f,
                                   (float)frame_width, (float)frame_height});

  PlayerAnimation playerAnimation = {
      .atlas = atlas,
      .frame_per_second = frame_per_second,
      .rectangles = NULL,
      .rectangles_lenght = length,
  };

  Rectangle *mem = (Rectangle *)malloc(sizeof(Rectangle) * length);
  if (mem == NULL) {
    TraceLog(LOG_FATAL, "No memory for CreateSpriteAnimation");
    playerAnimation.rectangles_lenght = 0;
    return playerAnimation;
  }

  playerAnimation.rectangles = mem;

  for (int i = 0; i < length; i++)
    playerAnimation.rectangles[i] = rectangles[i];

  return playerAnimation;
}

Texture2D AnimationFrames(std::string route, int px_width, int px_height) {
  Texture2D _a;
  Image image;
  fs::path route_path = route;
  if (fs::exists(route_path) && fs::is_directory(route_path)) {

    std::vector<std::string> files;

    for (const auto &input : fs::directory_iterator(route_path))
      files.push_back(input.path().string());

    std::sort(files.begin(), files.end());
    Image image_terminated =
        GenImageColor(files.size() * px_width, px_height, BLANK);
    int i = 0;
    for (const auto &file : files) {
      image = LoadImage(file.c_str());
      Rectangle src_rec = {0.0f, 0.0f, (float)image.width, (float)image.height};
      Rectangle dst_rec = {(float)(i * px_width), 0.0f, (float)px_width,
                           (float)px_height};
      ImageDraw(&image_terminated, image, src_rec, dst_rec, WHITE);
      i++;
      UnloadImage(image);
    }
    _a = LoadTextureFromImage(image_terminated);
    UnloadImage(image_terminated);
  }

  return _a;
}

void DisposeSpriteAnimation(PlayerAnimation animation) {
  free(animation.rectangles);
  UnloadTexture(animation.atlas);
};

void DrawPlayerAnimationPro(PlayerAnimation animation, Rectangle dest,
                            Vector2 origin, float rotation, Color tint) {
  int index = (int)(GetTime() * animation.frame_per_second) %
              animation.rectangles_lenght;
  Rectangle source = animation.rectangles[index];
  DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}
