#include "utils.h"

void wrap_coordinates(float *x, float *y, float w, float h) {
    if (*x + w > (float)SCREEN_WIDTH) {
        *x = 0;
    }
    if (*x < 0) {
        *x = SCREEN_WIDTH - w;
    }
    if (*y > (float)SCREEN_HEIGHT) {
        *y = 0;
    }
    if (y < 0) {
        *y = (float)(SCREEN_HEIGHT - (h * 0.5f));
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