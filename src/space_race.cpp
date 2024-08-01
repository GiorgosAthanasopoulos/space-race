#include <raylib.h>
#include <sstream>

#include "config.hpp"
#include "space_race.hpp"
#include "util.hpp"

SpaceRace::SpaceRace()
    : p1({KEY_P1_MOVE_UP, KEY_P1_MOVE_DOWN, true}),
      p2({KEY_P2_MOVE_UP, KEY_P2_MOVE_DOWN, false}) {
  winSize = GetWindowSize();
  Restart();

  PlayMusicStream(am.bgm);
}

SpaceRace::~SpaceRace() {}

void SpaceRace::Update() {
  HandleMusic();
  HandlePause();
  if (paused) {
    return;
  }
  if (winner != NONE) {
    HandleLoss();
    return;
  }
  HandlePlayers();
  HandleEnemies();
  HandleTimers();
}

void SpaceRace::Draw() {
  ClearBackground(WIN_BG);

  if (paused) {
    DrawPaused();
    return;
  }

  if (winner != NONE) {
    DrawWinner();
    return;
  }

  DrawTexturePro(am.bg, {0, 0, (float)am.bg.width, (float)am.bg.height},
                 {0, 0, winSize.x, winSize.y}, {0, 0}, 0, WHITE);
  DrawScores();
  DrawEntities();
  DrawTimer();
}

void SpaceRace::Resize(Vector2 old, Vector2 nnew) {
  winSize = nnew;

  p1.Resize(old, nnew);
  p2.Resize(old, nnew);
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Resize(old, nnew);
  }
}

void SpaceRace::Restart() {
  p1.Reset();
  p2.Reset();
  score1 = score2 = 0;
  enemies.clear();
  enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
  gameTimer = GAME_TIMER;
  winner = NONE;
  paused = false;
}

void SpaceRace::HandleMusic() {
  if (IsKeyPressed(KEY_MUTE)) {
    if (IsMusicStreamPlaying(am.bgm)) {
      PauseMusicStream(am.bgm);
    } else {
      ResumeMusicStream(am.bgm);
    }
  }
  UpdateMusicStream(am.bgm);
}

void SpaceRace::HandleLoss() {
  if (winner != NONE) {
    if (IsKeyPressed(KEY_RESTART)) {
      Restart();
    }
    return;
  }
}

void SpaceRace::HandleEnemies() {
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Update();

    Rectangle enemyRec = enemies[i].GetRec();
    if (CheckCollisionRecs(enemyRec, p1.GetRec())) {
      p1.Reset();
    }
    if (CheckCollisionRecs(enemyRec, p2.GetRec())) {
      p2.Reset();
    }
  }
}

void SpaceRace::HandlePlayers() {
  p1.Update();
  p2.Update();
  if (p1.GetRec().y < 0) {
    p1.Reset();
    score1++;
  }
  if (p2.GetRec().y < 0) {
    p2.Reset();
    score2++;
  }
}

void SpaceRace::HandleTimers() {
  float frameTime = GetFrameTime();
  enemySpawnTimer -= frameTime;
  if (enemySpawnTimer <= 0.0f) {
    enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    enemies.push_back(Enemy());
  }

  gameTimer -= frameTime;
  if (gameTimer <= 0.0f) {
    winner = score1 > score2 ? P1 : score1 == score2 ? DRAW : P2;
  }
}

void SpaceRace::DrawWinner() {
  const char *winnerText = winner == P1   ? "Winner: P1"
                           : winner == P2 ? "Winner: P2"
                                          : "Winner: Draw";
  Vector2 winnerTextSize = AssertTextFitsInViewport(winnerText, LARGE_FONT_SIZE,
                                                    GetWindowSize() / 2);
  DrawText(winnerText, winSize.x / 2 - winnerTextSize.x / 2,
           winSize.y / 2 - winnerTextSize.y / 2, winnerTextSize.y,
           SCORE_TEXT_COLOR);
}

void SpaceRace::DrawScores() {
  std::ostringstream s1ss;
  s1ss << score1;
  std::string s1s = s1ss.str();
  const char *s1 = s1s.data();
  Vector2 maxSize = GetWindowSize() / 6;
  Vector2 s1Size = AssertTextFitsInViewport(s1, FONT_SIZE, maxSize);
  DrawText(s1, 0, winSize.y - s1Size.y - SCORE_TEXT_PADDING, s1Size.y,
           SCORE_TEXT_COLOR);

  std::ostringstream s2ss;
  s2ss << score2;
  std::string s2s = s2ss.str();
  const char *s2 = s2s.data();
  Vector2 s2Size = AssertTextFitsInViewport(s2, FONT_SIZE, maxSize);
  DrawText(s2, winSize.x - s2Size.x - SCORE_TEXT_PADDING,
           winSize.y - s2Size.y - SCORE_TEXT_PADDING, s2Size.y,
           SCORE_TEXT_COLOR);
}

void SpaceRace::DrawEntities() {
  p1.Draw(am.rocket);
  p2.Draw(am.rocket);
  for (size_t i = 0; i < enemies.size(); ++i) {
    enemies[i].Draw(am.debris);
  }
}

void SpaceRace::DrawTimer() {
  float height = gameTimer * TIMER_HEIGHT_MULTIPLIER;
  DrawRectangle(winSize.x / 2 - (float)TIMER_THICK / 2, winSize.y - height,
                TIMER_THICK, height, TIMER_COLOR);
}

void SpaceRace::DrawPaused() {
  const char *text = "Paused";
  Vector2 textSize =
      AssertTextFitsInViewport(text, LARGE_FONT_SIZE, GetWindowSize() / 2);
  DrawText(text, winSize.x / 2 - textSize.x / 2, winSize.y / 2 - textSize.y / 2,
           textSize.y, SCORE_TEXT_COLOR);
}

void SpaceRace::HandlePause() {
  if (IsKeyPressed(KEY_PAUSE_GAME)) {
    paused = !paused;
  }
}
