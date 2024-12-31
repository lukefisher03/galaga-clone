#ifndef STAR_H
#define STAR_H

#include <SDL3/SDL.h>

struct Player;

struct Star {
    SDL_FRect r;
    // 0-255
    char brightness;
    char velocity;
    // 4 bytes
    char red, green, blue;
};

void initialize_stars(struct Star star_arr[], size_t size);
void render_stars(struct Star stars[], SDL_Renderer *renderer,
                  struct Player *player);
#endif