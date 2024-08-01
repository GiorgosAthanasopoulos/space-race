#include <raylib.h>

#include "config.hpp"
#include "player.hpp"
#include "util.hpp"

Player::Player(PlayerConfig pc) {
  this->pc = pc;
  Resize(GetWindowSize(), GetWindowSize());
}

Player::~Player() {}

void Player::Update() {
  Vector2 vel = {0, 0};
  if (IsKeyDown(pc.keyMoveUp) && IsKeyDown(pc.keyMoveDown)) {
    vel.y = 0;
  } else if (IsKeyDown(pc.keyMoveUp)) {
    vel.y = -speed.y;
  } else if (IsKeyDown(pc.keyMoveDown)) {
    vel.y = speed.y;
  }
  pos += vel * GetFrameTime();
  WorldBoundaryCheck(&pos, size);
}

void Player::Draw(Texture2D tex) {
  Rectangle playerRec = GetRec();
  DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, playerRec,
                 {0, 0}, 0, WHITE);
  if (DEBUG) {
    DrawRectangleLinesEx(playerRec, DEBUG_HTBX_THICK, DEBUG_HTBX_COLOR);
  }
}

void Player::Resize(Vector2 old, Vector2 nnew) {
  speed = CalculateSpeed(PLAYER_SPEED_RATIO);
  size = CalculateSize(PLAYER_SIZE_RATIO);
  pos = MaintainPosAfterResize(old, nnew, pos);
}

Rectangle Player::GetRec() { return {pos.x, pos.y, size.x, size.y}; }

void Player::Reset() {
  pos = {GetWindowWidth() * (pc.playerLeft ? 1 : 2) / 3,
         GetWindowHeight() - size.y * 2};
}
