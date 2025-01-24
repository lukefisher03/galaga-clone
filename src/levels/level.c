#include "level.h"
#include "../config.h"

void render_level(struct Level *level, SDL_Renderer *renderer) {
    printf("Rendering level!\n");
    if (!level || !renderer) {
        printf("Failed to render level");
        return;
    }

    for (size_t i = 0; i < level->num_clusters; ++i) {
        struct EnemyCluster *cluster = &level->enemy_clusters[i];
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        // SDL_RenderRect(renderer, &cluster->box);
        if (cluster->shift_distance) {
            if (cluster->enemies[0].rect.x >
                cluster->box.x + cluster->shift_distance) {
                cluster->direction *= -1;
            } else if (cluster->enemies[0].rect.x < cluster->box.x) {
                cluster->direction *= -1;
            }
        }

        if (cluster->size != 0) {
            for (size_t j = 0; j < cluster->size; ++j) {
                struct Enemy *e = &cluster->enemies[j];
                printf("\tRendering enemy! x: %f, y: %f\n", e->rect.x,
                       e->rect.y);

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