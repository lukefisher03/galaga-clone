#ifndef BULLET_H
#define BULLET_H

#include "player.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include "config.h"

typedef struct Bullet
{
  SDL_FRect rect;
  float velocity;
} Bullet;

Bullet *create_bullet(Player *p);

#endif