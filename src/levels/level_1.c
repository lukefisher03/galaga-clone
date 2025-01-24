#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
#include "level.h"

struct Level *build_level_1(SDL_Renderer *renderer) {
    struct Level *level = malloc(sizeof(struct Level));

    if (!level) {
        printf("Failed to allocate space for level 1");
        return NULL;
    }

    level->num_clusters = 2;
    printf("num clusters: %i\n", level->num_clusters);
    level->enemy_clusters =
        calloc(level->num_clusters, sizeof(struct EnemyCluster));

    if (!level->enemy_clusters) {
        printf("Failed to allocate space enemy clusters");
        return NULL;
    }

    level->enemy_clusters[0] =
        *create_enemy_cluster(5, 20, 100, 400, level, NULL, renderer);
    level->enemy_clusters[1] =
        *create_enemy_cluster(5, 300, 300, 600, level, NULL, renderer);

    return level;
}

void update_level_1(struct Level *level) {
    // blank for now
}