#include "player.h"
#include "config.h"
#include "enemy.h"
#include "utils.h"

void initialize_player(struct Player *p, SDL_Renderer *renderer) {
    p->rect.x = (SCREEN_WIDTH - SHIP_SIZE) / 2.0f;
    p->rect.y = (SCREEN_HEIGHT - SHIP_SIZE) * 0.85f;
    p->rect.w = SHIP_SIZE;
    p->rect.h = SHIP_SIZE;

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
    if (p->wasd & 1 && p->rect.y > (SCREEN_HEIGHT / 1.5)) {
        p->rect.y -= PLAYER_SPEED;
    }
    if (p->wasd & 4 && (p->rect.y + SHIP_SIZE) < SCREEN_HEIGHT) {
        p->rect.y += PLAYER_SPEED;
    }
    if (p->wasd & 2) {
        p->rect.x -= PLAYER_SPEED;
    }
    if (p->wasd & 8) {
        p->rect.x += PLAYER_SPEED;
    }

    wrap_coordinates(&p->rect);
}

unsigned int check_player_bullet_collision(struct Player *player,
                                           struct Bullet **bullets,
                                           struct QTNode *q_tree,
                                           SDL_Renderer *renderer) {
    unsigned int collision_count = 0;
    for (size_t i = 0; i < player->bullets_fired; ++i) {
        struct Bullet *b = bullets[i];
        b->rect.y -= BULLET_SPEED;
        b->rect.x += i % 2 == 0 ? b->velocity : -b->velocity;

        struct Enemy *collided_enemy = qt_query(q_tree, &b->rect);
        if (collided_enemy != NULL) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderRect(renderer, &collided_enemy->rect);
            collided_enemy->health -= 35;
            if (collided_enemy->health <= 0) {
                collision_count += 1;
            }
        }

        if (b->rect.y < 0 || collided_enemy != NULL) {
            free(bullets[i]);
            /* This keeps a compact array. The bullet is freed and a
             * hole is created in the array, so automatically move the
             * last bullet into that space and decrement the bullet
             * count. The order of the array elements doesn't matter.
             */

            bullets[i] = bullets[--player->bullets_fired];
        }

        SDL_SetRenderDrawColor(renderer, 3, 215, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderRect(renderer, &(b->rect));
    }
    return collision_count;
}