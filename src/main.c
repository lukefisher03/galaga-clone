#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "player.h"
#include "quadtree.h"
#include "star.h"
#include "utils.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static struct Star stars[NUM_STARS];

struct AppState {
    int paused; // 4 bytes
    struct Bullet *bullets[NUM_BULLETS];
    struct EnemyCluster enemy_cluster;
    struct Player player;
};

Uint32 fire_weapon(void *as, SDL_TimerID id, Uint32 interval) {
    struct AppState *state = (struct AppState *)(as);

    if (state->paused) {
        return interval;
    }

    struct Player *p = &state->player;
    if (p->wasd & 16 && p->bullets_fired < NUM_BULLETS) {
        struct Bullet *b = create_bullet(p);
        state->bullets[++p->bullets_fired - 1] = b;
    }
    return interval;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    struct AppState *as = SDL_calloc(1, sizeof(struct AppState));
    struct Player *player = &as->player;

    if (!as) {
        return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Sample SDL Project", SCREEN_WIDTH,
                                     SCREEN_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't initialize SDL window and renderer: %s\n",
                SDL_GetError());
        return SDL_APP_FAILURE;
    }

    initialize_player(player, renderer);
    initialize_enemies(&as->enemy_cluster, renderer);
    initialize_stars(stars, NUM_STARS);

    *appstate = as;

    SDL_AddTimer(100, &fire_weapon, as);

    SDL_SetRenderVSync(renderer, 1);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

    struct Player *player = &((struct AppState *)(appstate))->player;
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_WINDOW_FOCUS_LOST) {
        ((struct AppState *)appstate)->paused = 1;
        return SDL_APP_CONTINUE;
    }

    if (event->type == SDL_EVENT_WINDOW_FOCUS_GAINED) {
        ((struct AppState *)appstate)->paused = 0;
        return SDL_APP_CONTINUE;
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        ((struct AppState *)appstate)->paused = !((struct AppState *)appstate)->paused;
    }

    handle_input(event, player);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Uint64 start = SDL_GetTicksNS();

    struct QTNode *q_tree = calloc(1, sizeof(struct QTNode));

    qt_initialize(q_tree, SCREEN_WIDTH, SCREEN_HEIGHT);

    struct AppState *as = (struct AppState *)(appstate);
    struct Player *player = &(as->player);

    update_player_movement(player);

    if (as->paused) {
        SDL_Delay(500);
        return SDL_APP_CONTINUE;
    }

    SDL_SetRenderDrawColor(renderer, 10, 15, 20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    render_enemies(&as->enemy_cluster, renderer, q_tree);

    for (size_t i = 0; i < player->bullets_fired; ++i) {
        struct Bullet *b = as->bullets[i];
        b->rect.y -= BULLET_SPEED;
        b->rect.x += i % 2 == 0 ? b->velocity : -b->velocity;

        struct Enemy *collided_enemy = qt_query(q_tree, &b->rect);
        if (collided_enemy != NULL) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderRect(renderer, &collided_enemy->rect);
            collided_enemy->health = 0;
        }

        if (b->rect.y < 0 || collided_enemy != NULL) {
            free(as->bullets[i]);
            /* This keeps a compact array. The bullet is freed and a
             * hole is created in the array, so automatically move the
             * last bullet into that space and decrement the bullet
             * count. The order of the array elements doesn't matter.
             */

            as->bullets[i] = as->bullets[--player->bullets_fired];
        }

        SDL_SetRenderDrawColor(renderer, 3, 215, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderRect(renderer, &(b->rect));
    }

    render_stars(stars, renderer, player);
    qt_print_tree(q_tree, renderer);
    wrap_coordinates(&player->x, &player->y, SHIP_SIZE, SHIP_SIZE);

    SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderTexture(renderer, player->texture, NULL, &player->rect);
    SDL_RenderDebugText(renderer, 20, 20, "GALAGA!");
    SDL_RenderPresent(renderer);

    qt_free(q_tree);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyTexture(texture);
}