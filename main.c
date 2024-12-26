#define SDL_MAIN_USE_CALLBACKS 1

#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "config.h"
#include "player.h"
#include "star.h"
#include "bullet.h"
#include "utils.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static Bullet *bullets[NUM_BULLETS];
static Star stars[NUM_STARS];

typedef struct AppState
{
  int paused;
  Player player;
} AppState;

Uint32 fire_weapon(void *player, SDL_TimerID id, Uint32 interval)
{
  Player *p = (Player *)(player);
  if (p->wasd & 16 && p->bullets_fired < NUM_BULLETS)
  {
    Bullet *b = create_bullet(player);
    bullets[++p->bullets_fired - 1] = b;
  }
  return interval;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  AppState *as = SDL_calloc(1, sizeof(AppState));
  Player *player = &as->player;

  if (!as)
  {
    return SDL_APP_FAILURE;
  }

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Sample SDL Project", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer))
  {
    SDL_Log("Couldn't initialize SDL window and renderer: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  initialize_player(player, renderer);
  initialize_stars(stars, NUM_STARS);

  *appstate = as;

  SDL_AddTimer(100, &fire_weapon, player);

  SDL_SetRenderVSync(renderer, 1);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{

  Player *player = &((AppState *)(appstate))->player;
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  }

  if (event->type == SDL_EVENT_WINDOW_FOCUS_LOST)
  {
    ((AppState *)appstate)->paused = 1;
    return SDL_APP_CONTINUE;
  }

  if (event->type == SDL_EVENT_WINDOW_FOCUS_GAINED)
  {
    ((AppState *)appstate)->paused = 0;
    return SDL_APP_CONTINUE;
  }

  handle_input(event, player);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  Uint64 start = SDL_GetTicksNS();
  AppState *as = (AppState *)(appstate);
  Player *player = &(as->player);

  update_player_movement(player);

  if (as->paused)
  {
    SDL_Delay(500);
    return SDL_APP_CONTINUE;
  }

  SDL_SetRenderDrawColor(renderer, 16, 20, 31, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  for (size_t i = 0; i < player->bullets_fired; ++i)
  {
    Bullet *b = bullets[i];
    b->rect.y -= BULLET_SPEED;
    b->rect.x += i % 2 == 0 ? b->velocity : -b->velocity;

    if (b->rect.y < 0)
    {
      free(bullets[i]);
      /* This keeps a compact array. The bullet is freed and a hole is created in the array,
       * so automatically move the last bullet into that space and decrement the bullet count.
       * The order of the array elements doesn't matter.
       */

      bullets[i] = bullets[--player->bullets_fired];
    }

    SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &(b->rect));
  }

  render_stars(stars, renderer);

  wrap_coordinates(&player->x, &player->y, player->size, player->size);

  SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
  // SDL_RenderFillRects(renderer, stars, NUM_STARS);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderTexture(renderer, player->texture, NULL, &player->rect);
  SDL_RenderDebugText(renderer, 20, 20, "GALAGA!");
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  SDL_DestroyTexture(texture);
}