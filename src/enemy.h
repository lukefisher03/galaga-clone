#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>

struct QTNode;
struct Bullet;

struct Enemy {
    float x, y;
    SDL_FRect rect;
    int health;
};

struct EnemyCluster {
    SDL_Texture *texture;
    struct Enemy *enemies;
    int size;
};

struct EnemyCluster *create_enemy_cluster(int count, SDL_Renderer *renderer);
void initialize_default_enemy(struct Enemy *e, int x, int y);

#endif