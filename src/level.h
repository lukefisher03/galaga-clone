#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "config.h"
#include "enemy.h"

struct Level {
    // Resizable array of enemy clusters
    struct EnemyCluster **enemy_clusters;
    // Total number of enemies for the entire level
    int num_enemies;
    // Total number of clusters for the entire level
    int num_clusters;
};

struct Level *build_level_1(SDL_Renderer *renderer);

#endif