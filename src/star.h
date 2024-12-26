#ifndef STAR_H
#define STAR_H
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "utils.h"
#include "config.h"
#include "player.h"
typedef struct Star
{
  SDL_FRect r;
  // 0-255
  char brightness;
  char velocity;
  // 4 bytes
  char red, green, blue;
} Star;

void initialize_stars(Star star_arr[], size_t size);
void render_stars(Star stars[], SDL_Renderer *renderer, Player *player);
#endif