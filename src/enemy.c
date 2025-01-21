#include "enemy.h"
#include "quadtree.h"
#include "config.h"


struct EnemyCluster *create_enemy_cluster(int size, SDL_Renderer *renderer) {
    if (size > MAX_ENEMY_CLUSTER_SIZE) {
        printf("Attempted to allocate enemy cluster larger than: %i.",
               MAX_ENEMY_CLUSTER_SIZE);
        return NULL;
    }

    struct EnemyCluster *enemy_cluster = malloc(sizeof(struct EnemyCluster));
    if (!enemy_cluster) {
        printf("Failed to allocate enemy cluster");
        return NULL;
    }
    enemy_cluster->size = size;
    enemy_cluster->enemies = calloc(size, sizeof(struct Enemy));

    if (!enemy_cluster->enemies) {
        printf("Failed to allocate enemies array in new Enemy Cluster");
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

    for (size_t i = 0; i < size; ++i) {
        struct Enemy e = enemy_cluster->enemies[i];
        e.health = MAX_ENEMY_HEALTH;
    }

    return enemy_cluster;
}

void initialize_default_enemy(struct Enemy *e, int x, int y) {
    e->health = 100;
    e->x = x;
    e->y = y;

    SDL_FRect r;
    r.w = SHIP_SIZE;
    r.h = SHIP_SIZE;
    r.x = x;
    r.y = y;
}

