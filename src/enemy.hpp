#pragma once

#include <raylib.h>

class Enemy {
public:
  Enemy();
  ~Enemy();
  void Update();
  void Draw(Texture2D tex);
  void Resize(Vector2 old, Vector2 nnew);
  Rectangle GetRec();

private:
  Vector2 pos, speed, size;
  bool ltr;
};
