#pragma once

// == WINDOW ==
#define WIN_FLAGS FLAG_WINDOW_RESIZABLE
#define WIN_W 1280
#define WIN_H 720
#define WIN_TITLE "SpaceRace"
#define WIN_FPS 60
#define WIN_MIN_W 640
#define WIN_MIN_H 480
#define WIN_MAX_W 3840
#define WIN_MAX_H 2160
#define WIN_BG BLACK
// == WINDOW ==

// == KEYBIND ==
#define KEY_EXIT KEY_NULL
#define KEY_P1_MOVE_UP KEY_W
#define KEY_P1_MOVE_DOWN KEY_S
#define KEY_P2_MOVE_UP KEY_UP
#define KEY_P2_MOVE_DOWN KEY_DOWN
#define KEY_RESTART KEY_SPACE
#define KEY_MUTE KEY_M
#define KEY_PAUSE_GAME KEY_P
// == KEYBIND ==

// == DEBUG ==
#define DEBUG false
#define DEBUG_HTBX_THICK 1
#define DEBUG_HTBX_COLOR RED
// == DEBUG ==

// == PLAYER ==
#define PLAYER_SIZE_RATIO 15
#define PLAYER_SPEED_RATIO 2
// == PLAYER ==

// == MUSIC ==
#define MUSIC_VOLUME 1.0f
// == MUSIC ==

// == ENEMY ==
#define ENEMY_SPEED_RATIO 3
#define ENEMY_SIZE_RATIO 15
#define ENEMY_SPAWN_INTERVAL 0.3f
// == ENEMY ==

// == UI ==
#define FONT_SIZE 100
#define LARGE_FONT_SIZE 1000
#define SCORE_TEXT_PADDING 5
#define SCORE_TEXT_COLOR WHITE
// == UI ==

// == GAME ==
#define GAME_TIMER 20
#define TIMER_THICK 10
#define TIMER_COLOR WHITE
#define TIMER_HEIGHT_MULTIPLIER 10
// == GAME ==
