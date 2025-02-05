#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "quadtree.h"
#include "bullet.h"

struct AppState;

struct Player {
    int bullets_fired;
    char wasd;
    char lives;
    SDL_Texture *texture;
    SDL_FRect rect;
};

void initialize_player(struct Player *p, struct AppState *as, SDL_Renderer *renderer);
void handle_input(SDL_Event *e, struct Player *p);
void update_player_movement(struct Player *p);
unsigned int update_bullets(struct Player *player,
                                           struct Bullet **bullets,
                                           struct QTNode *q_tree,
                                           SDL_Renderer *renderer);
Uint32 fire_player_weapon(void *as, SDL_TimerID id, Uint32 interval);

#endif