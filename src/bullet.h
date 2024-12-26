#ifndef BULLET_H
#define BULLET_H

#include "player.h"

#include "config.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

struct Bullet {
    SDL_FRect rect;
    float velocity;
};

struct Bullet *create_bullet(struct Player *p);

#endif