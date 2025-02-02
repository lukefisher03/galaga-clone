#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "quadtree.h"
#include "bullet.h"

struct Player {
    int bullets_fired;
    char wasd;
    SDL_Texture *texture;
    SDL_FRect rect;
};

void initialize_player(struct Player *p, SDL_Renderer *renderer);
void handle_input(SDL_Event *e, struct Player *p);
void update_player_movement(struct Player *p);
unsigned int check_player_bullet_collision(struct Player *player,
                                           struct Bullet **bullets,
                                           struct QTNode *q_tree,
                                           SDL_Renderer *renderer);

#endif