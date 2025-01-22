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
    printf("Enemey cluster 0: %i", level->enemy_clusters[0].size);
    printf("Running build level\n");
    for (size_t i = 0; i < level->num_clusters; ++i) {
        printf("%lu\n", i);
        struct EnemyCluster *cluster = &level->enemy_clusters[i];
        cluster->enemies = calloc(5, sizeof(struct Enemy));
        cluster->texture = load_bmp_texture("assets/enemy.bmp", renderer);
        cluster->size = 5;
    }

    struct EnemyCluster *cluster1 = &level->enemy_clusters[0];
    for (size_t j = 0; j < cluster1->size; ++j) {
        initialize_default_enemy(&cluster1->enemies[j],
                                 300 + ((SHIP_SIZE + 50) * j), 200);
    }

    struct EnemyCluster *cluster2 = &level->enemy_clusters[1];
    for (size_t j = 0; j < cluster2->size; ++j) {
        initialize_default_enemy(&cluster2->enemies[j],
                                 700 + ((SHIP_SIZE + 50) * j), 400);
    }

    return level;
}