#include "player.h"

void initialize_player(struct Player *p, SDL_Renderer *renderer) {
    SDL_Surface *surface = NULL;
    char *bmp_path = NULL;

    p->x = (SCREEN_WIDTH - SHIP_SIZE) / 2.0f;
    p->y = (SCREEN_HEIGHT - SHIP_SIZE) * 0.85f;
    p->bullets_fired = 0;

    SDL_asprintf(&bmp_path, "%sassets/ship.bmp", SDL_GetBasePath());
    printf("Initializing player from bmp at path: %s\n", bmp_path);
    surface = SDL_LoadBMP("assets/ship.bmp");

    if (!surface) {
        SDL_Log("Failed to load bmp at %s\n", bmp_path);
    }

    SDL_free(bmp_path);

    p->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!p->texture) {
        SDL_Log("Failed to create texture from surface: %s\n", SDL_GetError());
    }

    SDL_DestroySurface(surface);
}

void handle_input(SDL_Event *e, struct Player *p) {
    if (e->type == SDL_EVENT_KEY_DOWN) {
        switch (e->key.scancode) {
        case SDL_SCANCODE_W:
            p->wasd |= 1;
            break;
        case SDL_SCANCODE_A:
            p->wasd |= 2;
            break;
        case SDL_SCANCODE_S:
            p->wasd |= 4;
            break;
        case SDL_SCANCODE_D:
            p->wasd |= 8;
            break;
        case SDL_SCANCODE_SPACE:
            p->wasd |= 16;
            break;
        default:
            break;
        }
    }

    if (e->type == SDL_EVENT_KEY_UP) {
        switch (e->key.scancode) {
        case SDL_SCANCODE_W:
            p->wasd &= 30;
            break;
        case SDL_SCANCODE_A:
            p->wasd &= 29;
            break;
        case SDL_SCANCODE_S:
            p->wasd &= 27;
            break;
        case SDL_SCANCODE_D:
            p->wasd &= 23;
            break;
        case SDL_SCANCODE_SPACE:
            p->wasd &= 15;
            break;
        default:
            break;
        }
    }
}

void update_player_movement(struct Player *p) {
    if (p->wasd & 1 && p->y > (SCREEN_HEIGHT / 1.5)) {
        p->y -= PLAYER_SPEED;
    }
    if (p->wasd & 4 && (p->y + SHIP_SIZE) < SCREEN_HEIGHT) {
        p->y += PLAYER_SPEED;
    }
    if (p->wasd & 2) {
        p->x -= PLAYER_SPEED;
    }
    if (p->wasd & 8) {
        p->x += PLAYER_SPEED;
    }

    p->rect.x = p->x;
    p->rect.y = p->y;
    p->rect.w = SHIP_SIZE;
    p->rect.h = SHIP_SIZE;
}