#include "level.h"

void render_level(struct Level *level, SDL_Renderer *renderer) {
    printf("Rendering level!\n");
    if (!level || !renderer) {
        printf("Failed to render level");
        return;
    }

    for (size_t i = 0; i < level->num_clusters; ++i) {
        for (size_t j = 0; j < level->enemy_clusters[i].size; ++j) {
            struct Enemy *e = &level->enemy_clusters[i].enemies[j];
            printf("\tRendering enemy! x: %f, y: %f\n", e->rect.x, e->rect.y);

            if (e->health > 0) {
                qt_add_node(level->q_tree, e);
                SDL_RenderTexture(renderer, level->enemy_clusters[i].texture,
                                  NULL, &e->rect);
            }
        }
    }
}