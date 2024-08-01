#pragma once

#include <raylib.h>
#include <vector>

#include "asset_manager.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "winner.hpp"

class SpaceRace {
public:
  SpaceRace();
  ~SpaceRace();
  void Update();
  void Draw();
  void Resize(Vector2 old, Vector2 nnew);

private:
  Vector2 winSize;
  Player p1, p2;
  AssetManager am;
  std::vector<Enemy> enemies;
  int score1, score2;
  float enemySpawnTimer;
  float gameTimer;
  Winner winner;

  void Restart();
  void HandleMusic();
  void HandleLoss();
  void HandleEnemies();
  void HandlePlayers();
  void HandleTimers();
  void DrawWinner();
  void DrawScores();
  void DrawEntities();
  void DrawTimer();
};
