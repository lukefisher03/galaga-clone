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
    int direction;
    struct Enemy enemies[NUM_ENEMIES];
};

void initialize_enemies(struct EnemyCluster *enemy_cluster,
                        SDL_Renderer *renderer);
void render_enemies(struct EnemyCluster *enemy_cluster, SDL_Renderer *renderer,
                    struct QTNode *q_tree);

void check_bullet_collision(struct Bullet *b,
                            struct EnemyCluster *enemy_cluster);
#endif