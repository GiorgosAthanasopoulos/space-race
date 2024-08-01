#include <raylib.h>

#include "asset_manager.hpp"
#include "config.hpp"

AssetManager::AssetManager() {
  rocket = LoadTexture("assets/ship_1.png");
  debris = LoadTexture("assets/meteor.png");
  bg = LoadTexture("assets/background_stars.png");

  bgm = LoadMusicStream("assets/bgm.mp3");
  SetMusicVolume(bgm, MUSIC_VOLUME);
}

AssetManager::~AssetManager() {
  UnloadTexture(rocket);
  UnloadTexture(debris);
  UnloadTexture(bg);

  UnloadMusicStream(bgm);
}
