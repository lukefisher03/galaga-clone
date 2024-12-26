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