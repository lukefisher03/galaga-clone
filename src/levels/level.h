#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "../config.h"
#include "../enemy.h"
#include "../quadtree.h"

struct Level {
    // Resizable array of enemy clusters
    struct EnemyCluster *enemy_clusters;
    // Total number of enemies for the entire level
    int num_enemies;
    // Total number of clusters for the entire level
    int num_clusters;

    struct QTNode *q_tree;
};

struct Level *build_level_1(SDL_Renderer *renderer);
void render_level(struct Level *level, SDL_Renderer *renderer);
#endif