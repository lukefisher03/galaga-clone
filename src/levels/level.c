#include "level.h"
#include "../config.h"

int determine_cluster_direction(struct EnemyCluster *cluster);

void update_level(struct Level *level, SDL_Renderer *renderer) {
    if (!level || !renderer) {
        printf("Failed to render level");
        return;
    }

    for (size_t i = 0; i < level->num_clusters; ++i) {
        struct EnemyCluster *cluster = &level->enemy_clusters[i];
        cluster->direction *= determine_cluster_direction(cluster);
        if (cluster->size != 0) {
            for (size_t j = 0; j < cluster->size; ++j) {
                struct Enemy *e = &cluster->enemies[j];

                e->rect.x += cluster->direction * ENEMY_SPEED;

                if (e->health > 0) {
                    qt_add_node(level->q_tree, e);
                    SDL_RenderTexture(renderer, cluster->texture, NULL,
                                      &e->rect);
                }
            }
        }
    }
}

int determine_cluster_direction(struct EnemyCluster *cluster) {
    if (cluster->shift_distance) {
        if (cluster->enemies[0].rect.x >
            cluster->box.x + cluster->shift_distance) {
            return -1;
        } else if (cluster->enemies[0].rect.x < cluster->box.x) {
            return -1;
        }
    }

    return 1;
}