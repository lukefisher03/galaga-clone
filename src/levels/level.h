#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "../config.h"
#include "../enemy.h"
#include "../quadtree.h"

struct AppState;

struct Level {
    // Resizable array of enemy clusters
    struct EnemyCluster *enemy_clusters;
    // Total number of clusters for the entire level
    unsigned int num_clusters;
    unsigned int cluster_count;
    // Number of enemies left in the level
    unsigned int enemy_count;
    unsigned int enemy_bullets_fired;

    struct QTNode *q_tree;
};

struct Level *build_level_1(struct AppState *as, SDL_Renderer *renderer);
void update_level_1(struct Level *level1);

void render_level(struct AppState *as, SDL_Renderer *renderer);
#endif