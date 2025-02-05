#ifndef BULLET_H
#define BULLET_H

#include <SDL3/SDL.h>

#include "config.h"

struct Bullet {
    SDL_FRect rect;
    float velocity;
};

struct Bullet *create_bullet(SDL_FRect *entity_box);
void destroy_bullet(size_t bullet_index, struct Bullet **bullet_buffer, int final_bullet_index);

#endif