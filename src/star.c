#include "star.h"
#include "player.h"
#include "utils.h"

void initialize_stars(struct Star star_arr[], size_t size) {
    for (size_t i = 0; i < STAR_COUNT; ++i) {
        float size = (SDL_randf() * STAR_MAX_SIZE) + 1.0f;
        star_arr[i].r.x = SDL_randf() * SCREEN_WIDTH;
        star_arr[i].r.y = SDL_randf() * SCREEN_HEIGHT;
        star_arr[i].r.w = size, star_arr[i].r.h = size;

        star_arr[i].velocity = (SDL_randf() * STAR_MAX_VELOCITY) + 1.0f;

        star_arr[i].red = SDL_randf() * 150.0f;
        star_arr[i].green = (SDL_randf() * 20.0f) + 100.0f;
        star_arr[i].blue = (SDL_randf() * 20.0f) + 100.0f;
    }
}

void render_stars(struct Star stars[], SDL_Renderer *renderer,
                  struct Player *player) {
    for (size_t i = 0; i < STAR_COUNT; ++i) {
        stars[i].r.y += stars[i].velocity;

        // Stars sway back and forth slightly as the player moves
        if (player->wasd & 2) {
            stars[i].r.x += 0.5;
        }
        if (player->wasd & 8) {
            stars[i].r.x -= 0.5;
        }

        if (stars[i].r.y > (float)SCREEN_HEIGHT) {
            stars[i].r.y = 0;
            stars[i].r.x = SDL_randf() * SCREEN_WIDTH;
        }

        SDL_SetRenderDrawColor(renderer, stars[i].red, stars[i].green,
                               stars[i].blue, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &stars[i].r);
    }
}