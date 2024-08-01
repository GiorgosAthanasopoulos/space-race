#pragma once

#include <raylib.h>

class AssetManager {
public:
  Texture2D rocket, debris, bg;
  Music bgm;

  AssetManager();
  ~AssetManager();
};
