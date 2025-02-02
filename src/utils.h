#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include <SDL3/SDL.h>

void wrap_coordinates(SDL_FRect *rect);
SDL_Texture *load_bmp_texture(char *path, SDL_Renderer *renderer);

#endif