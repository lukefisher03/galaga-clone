#include <stdio.h>
#include <stdlib.h>

#include "level.h"

struct Level *build_level_1(SDL_Renderer *renderer) {
    struct Level *level = malloc(sizeof(struct Level));

    if (!level) {
        printf("Failed to allocate space for level 1");
        return NULL;
    }

    level->num_clusters = 1;

    level->enemy_clusters =
        calloc(level->num_clusters, sizeof(struct EnemyCluster));

    if (!level->enemy_clusters) {
        printf("Failed to allocate space enemy clusters");
        return NULL;
    }

    char *bmp_path = NULL;
    SDL_asprintf(&bmp_path, "%sassets/enemy.bmp", SDL_GetBasePath());

    SDL_Surface *bmp_surface = SDL_LoadBMP(bmp_path);
    SDL_free(bmp_path);

    if (!bmp_surface) {
        printf("Could not load texture for enemy cluster");
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_DestroySurface(bmp_surface);

    for (size_t i = 0; i < level->num_clusters; ++i) {
        struct EnemyCluster *cluster = level->enemy_clusters[i];
        cluster->enemies = calloc(5, sizeof(struct Enemy));

        for (size_t j = 0; j < 5; ++j) {
            // Initialize enemy
        }
    }
}