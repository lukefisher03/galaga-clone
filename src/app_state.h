#ifndef APP_STATE_H
#define APP_STATE_H

#include "player.h"
#include "bullet.h"
#include "levels/level.h"

struct AppState {
    int paused;
    struct Bullet *bullets[PLAYER_NUM_BULLETS];
    struct Bullet *enemy_bullets[ENEMY_BULLET_BUFFER_SIZE];
    struct Player player;
    struct Level *active_level;
};

#endif