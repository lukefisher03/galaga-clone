#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include <SDL3/SDL.h>

struct Player {
    float x;
    float y;
    int bullets_fired;
    char wasd;
    SDL_Texture *texture;
    SDL_FRect rect;
};

void initialize_player(struct Player *p, SDL_Renderer *renderer);
void handle_input(SDL_Event *e, struct Player *p);
void update_player_movement(struct Player *p);

#endif