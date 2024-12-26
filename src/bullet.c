#include "bullet.h"

struct Bullet *create_bullet(struct Player *p) {
    struct Bullet *b = malloc(sizeof(struct Bullet));
    b->rect.x = p->x + (SHIP_SIZE / 2);
    b->rect.y = p->y - (SHIP_SIZE * 0.05);
    b->velocity = SDL_randf();
    b->rect.h = 15;
    b->rect.w = 2;
    return b;
}