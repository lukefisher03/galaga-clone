#include "utils.h"

void wrap_coordinates(SDL_FRect *rect) {
    if (rect->x + rect->w > (float)SCREEN_WIDTH) {
        rect->x = 0;
    }
    if (rect->x < 0) {
        rect->x = SCREEN_WIDTH - rect->w;
    }
    if (rect->y > (float)SCREEN_HEIGHT) {
        rect->y = 0;
    }
    if (rect->y < 0) {
        rect->y = (float)(SCREEN_HEIGHT - (rect->h * 0.5f));
    }
}

SDL_Texture *load_bmp_texture(char *path, SDL_Renderer *renderer) {
    printf("Running load texture!\n");
    char *bmp_path = NULL;
    SDL_Surface *surface = NULL;

    SDL_asprintf(&bmp_path, "%s%s", SDL_GetBasePath(), path);
    surface = SDL_LoadBMP(bmp_path);

    if (!surface) {
        SDL_Log("Failed to load bmp at %s\n", bmp_path);
    }

    SDL_free(bmp_path);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Could not create texture from: %s\n", path);
        return NULL;
    }
    SDL_DestroySurface(surface);
    printf("Successfully loaded in texture: %s\n", path);
    return texture;
}