#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>

struct Level;

struct Enemy {
    SDL_FRect rect;
    int health;
};

struct EnemyCluster {
    SDL_Texture *texture;
    struct Enemy *enemies;
    int size;
    SDL_FRect box;
    int shift_distance;
    int direction;
};

struct EnemyCluster *create_enemy_cluster(int count, float x, float y,
                                          int shift_distance,
                                          struct Level *level,
                                          char *texture_path,
                                          SDL_Renderer *renderer);
void initialize_default_enemy(struct Enemy *e, int x, int y);

#endif