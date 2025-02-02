#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "levels/level.h"
#include "player.h"
#include "quadtree.h"
#include "star.h"
#include "utils.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static struct Star stars[STAR_COUNT];

struct AppState {
    int paused;
    struct Bullet *bullets[PLAYER_NUM_BULLETS];
    struct Bullet *enemy_bullets[ENEMY_BULLET_BUFFER_SIZE];
    struct Player player;
    struct Level *active_level;
};

Uint32 fire_weapon(void *as, SDL_TimerID id, Uint32 interval) {
    struct AppState *state = (struct AppState *)(as);

    if (state->paused) {
        return interval;
    }

    struct Player *p = &state->player;
    if (p->wasd & 16 && p->bullets_fired < PLAYER_NUM_BULLETS) {
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
    initialize_stars(stars, STAR_COUNT);
    as->active_level = build_level_1(renderer);
    *appstate = as;

    SDL_AddTimer(300, &fire_weapon, as);

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
        ((struct AppState *)appstate)->paused =
            !((struct AppState *)appstate)->paused;
    }

    handle_input(event, player);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    struct AppState *as = (struct AppState *)(appstate);
    struct Player *player = &(as->player);
    struct QTNode *q_tree = calloc(1, sizeof(struct QTNode));

    qt_initialize(q_tree, SCREEN_WIDTH, SCREEN_HEIGHT);
    update_player_movement(player);

    as->active_level->q_tree = q_tree;

    if (as->paused) {
        SDL_Delay(500);
        return SDL_APP_CONTINUE;
    }

    SDL_SetRenderDrawColor(renderer, 10, 15, 20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    render_level(as->active_level, renderer);

    unsigned int num_collisions = check_player_bullet_collision(&as->player, as->bullets, q_tree, renderer);
    as->active_level->enemy_count -= num_collisions;

    render_stars(stars, renderer, player);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderTexture(renderer, player->texture, NULL, &player->rect);
    SDL_RenderDebugText(renderer, 20, 20, "GALAGA!");
    if (as->active_level->enemy_count <= 0) {
        SDL_RenderDebugText(renderer, 200, 20, "YOU WIN!");
    }
    SDL_RenderPresent(renderer);

    qt_free(q_tree);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyTexture(texture);
}