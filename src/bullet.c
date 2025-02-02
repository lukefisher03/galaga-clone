#include "bullet.h"
#include "player.h"

struct Bullet *create_bullet(struct Player *p) {
    struct Bullet *b = malloc(sizeof(struct Bullet));
    b->rect.x = p->rect.x + (SHIP_SIZE / 2);
    b->rect.y = p->rect.y - (SHIP_SIZE * 0.05);
    b->velocity = SDL_randf() / 2;
    b->rect.h = 15;
    b->rect.w = 2;
    return b;
}