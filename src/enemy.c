#include "enemy.h"
#include "config.h"
#include "levels/level.h"
#include "quadtree.h"
#include "utils.h"

struct EnemyCluster *create_enemy_cluster(int size, float x, float y,
                                          int shift_distance,
                                          struct Level *level,
                                          char *texture_path,
                                          SDL_Renderer *renderer) {
    if (size > MAX_ENEMY_CLUSTER_SIZE) {
        printf("Attempted to allocate enemy cluster larger than: %i.",
               MAX_ENEMY_CLUSTER_SIZE);
        return NULL;
    }

    if (!texture_path) {
        texture_path = DEFAULT_ENEMY_BMP;
    }

    struct EnemyCluster *enemy_cluster = malloc(sizeof(struct EnemyCluster));
    if (!enemy_cluster) {
        printf("Failed to allocate enemy cluster");
        return NULL;
    }
    enemy_cluster->size = size;
    enemy_cluster->enemies = calloc(size, sizeof(struct Enemy));
    enemy_cluster->texture = load_bmp_texture(texture_path, renderer);
    enemy_cluster->box.x = x;
    enemy_cluster->box.y = y;
    enemy_cluster->box.w = (SHIP_SIZE + 10) * enemy_cluster->size;
    enemy_cluster->box.h = SHIP_SIZE;
    enemy_cluster->shift_distance = shift_distance;
    enemy_cluster->direction = 1;

    if (!enemy_cluster->enemies) {
        printf("Failed to allocate enemies array in new Enemy Cluster");
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        struct Enemy e = enemy_cluster->enemies[i];
        initialize_default_enemy(&enemy_cluster->enemies[i],
                                 x + ((SHIP_SIZE + 10) * i), y);
        level->enemy_count += 1;
        e.health = MAX_ENEMY_HEALTH;
    }

    level->cluster_count += 1;
    return enemy_cluster;
}

void initialize_default_enemy(struct Enemy *e, int x, int y) {
    e->health = 10;
    SDL_FRect r;
    r.w = SHIP_SIZE;
    r.h = SHIP_SIZE;
    r.x = x;
    r.y = y;

    e->rect = r;
}
