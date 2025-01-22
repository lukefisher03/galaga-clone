#include "player.h"
#include "config.h"
#include "utils.h"

void initialize_player(struct Player *p, SDL_Renderer *renderer) {
    p->x = (SCREEN_WIDTH - SHIP_SIZE) / 2.0f;
    p->y = (SCREEN_HEIGHT - SHIP_SIZE) * 0.85f;
    p->bullets_fired = 0;

    p->texture = load_bmp_texture("assets/ship.bmp", renderer);
    if (!p->texture) {
        SDL_Log("Failed to create ship texture\n");
    }
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