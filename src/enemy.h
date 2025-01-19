#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>

#include "config.h"

struct QTNode;
struct Bullet;

struct Enemy {
    float x, y;
    SDL_FRect rect;
    SDL_Texture *texture;
    int health;
};

struct EnemyCluster {
    struct Enemy *enemies;
    int size;
};

struct EnemyCluster *create_enemy_cluster(int count, SDL_Renderer *renderer);
struct Enemy *create_default_enemy(int x, int y);

#endif