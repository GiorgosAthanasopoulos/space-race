#include <raylib.h>

#include "config.hpp"
#include "enemy.hpp"
#include "util.hpp"

Enemy::Enemy() {
  ltr = GetRandomValue(0, 1) == 1;
  Resize(GetWindowSize(), GetWindowSize());
  pos = {ltr ? -size.x : GetWindowWidth() + size.x,
         (float)GetRandomValue(size.y, GetWindowHeight() * 2 / 3)};
}

Enemy::~Enemy() {}

void Enemy::Update() {
  Vector2 vel = {ltr ? speed.x : -speed.x, 0};
  pos += vel * GetFrameTime();
}

void Enemy::Draw(Texture2D tex) {
  Rectangle enemyRec = GetRec();
  DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, enemyRec,
                 {0, 0}, 0, WHITE);
  if (DEBUG) {
    DrawRectangleLinesEx(enemyRec, DEBUG_HTBX_THICK, DEBUG_HTBX_COLOR);
  }
}

void Enemy::Resize(Vector2 old, Vector2 nnew) {
  speed = CalculateSpeed(ENEMY_SPEED_RATIO);
  size = CalculateSize(ENEMY_SIZE_RATIO);
  pos = MaintainPosAfterResize(old, nnew, pos);
}

Rectangle Enemy::GetRec() { return {pos.x, pos.y, size.x, size.y}; }
