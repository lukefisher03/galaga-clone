#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

struct Player;

struct Bullet {
    SDL_FRect rect;
    float velocity;
};

struct Bullet *create_bullet(struct Player *p);

#endif