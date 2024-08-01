#include <raylib.h>

#include "raylib.hpp"
#include "space_race.hpp"
#include "util.hpp"

int main() {
  Raylib *r = new Raylib;
  SpaceRace *g = new SpaceRace;
  Vector2 winSize = GetWindowSize();

  while (!WindowShouldClose()) {
    if (IsWindowResized()) {
      Vector2 nnew = GetWindowSize();
      g->Resize(winSize, nnew);
      r->Resize(winSize, nnew);
      winSize = nnew;
    }

    g->Update();
    r->Update();

    BeginDrawing();
    g->Draw();
    r->Draw();
    EndDrawing();
  }

  delete g;
  delete r;
  return 0;
}
