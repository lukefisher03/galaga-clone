#include "bullet.h"

Bullet *create_bullet(Player *p)
{
  Bullet *b = malloc(sizeof(Bullet));
  b->rect.x = p->x + (SHIP_SIZE / 2);
  b->rect.y = p->y - (SHIP_SIZE * 0.05);
  b->velocity = SDL_randf();
  b->rect.h = 15;
  b->rect.w = 2;
  return b;
}