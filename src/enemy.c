#include "enemy.h"

void initialize_enemies(struct EnemyCluster *enemy_cluster, SDL_Renderer *renderer) {
    char *bmp_path = NULL;
    SDL_asprintf(&bmp_path, "%sassets/enemy.bmp", SDL_GetBasePath());
    printf("Initializing enemy from bmp at path: %s\n", bmp_path);
    enemy_cluster->direction = 1;
    for (size_t i = 0; i < NUM_ENEMIES; i++) {
        struct Enemy *e = &enemy_cluster->enemies[i];
        SDL_Surface *surface = SDL_LoadBMP(bmp_path);

        if (!surface) {
            SDL_Log("Failed to load bmp for enemy ship, error - \n%s",
                    SDL_GetError());
        }

        e->texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (!e->texture) {
            SDL_Log("Failed to create texture for enemy ship, error - \n%s",
                    SDL_GetError());
        }

        e->x = (float)(SHIP_SIZE * i);
        e->y = 100.0;
        e->health = 50;

        SDL_DestroySurface(surface);
    }

    SDL_free(bmp_path);
};

void render_enemies(struct EnemyCluster *enemy_cluster, SDL_Renderer *renderer) {
    if (enemy_cluster->enemies[0].x <= 0) {
        enemy_cluster->direction = 1;
    } 

    if (enemy_cluster->enemies[NUM_ENEMIES - 1].x + SHIP_SIZE >= SCREEN_WIDTH) {
        enemy_cluster->direction = -1;
    }

    for (size_t i = 0; i < NUM_ENEMIES; i++) {
        struct Enemy *e = &enemy_cluster->enemies[i];
        e->x += ENEMY_SPEED * enemy_cluster->direction;
        e->rect.x = e->x;
        e->rect.y = e->y;
        e->rect.w = SHIP_SIZE;
        e->rect.h = SHIP_SIZE;

        SDL_RenderTexture(renderer, e->texture, NULL, &e->rect);
    }
}
