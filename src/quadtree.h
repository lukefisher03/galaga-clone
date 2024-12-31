/**
 * Quad Tree implementation that stores SDL_FRect structs.
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define QT_NODE_CAPACITY 4
#define MAX_DEPTH NUM_ENEMIES
#define MAX_NODE_VALUES 10

struct Enemy;

enum QT_RESULT {
    QT_SUCCESS,             // 0
    QT_MAX_VALUES_OVERFLOW, // 1
    QT_MAX_DEPTH_EXCEEDED,  // 2
    QT_VALUE_OUT_OF_BOUNDS, // 3
    QT_MEMORY_ERROR         // 4
};

struct QTNode {
    struct Enemy *values[MAX_NODE_VALUES];
    struct QTNode *northwest;
    struct QTNode *northeast;
    struct QTNode *southeast;
    struct QTNode *southwest;
    SDL_FRect boundary;
    int is_leaf;
    int values_count;
};

enum QT_RESULT qt_add_node(struct QTNode *parent, struct Enemy *value);
enum QT_RESULT qt_subdivide(struct QTNode *parent);
char qt_locate_quad(SDL_FRect *boundary, SDL_FRect *r);
int qt_contains(SDL_FRect *boundary, SDL_FRect *r);
void qt_initialize(struct QTNode *parent, float width, float height);
void qt_free(struct QTNode *parent);
void qt_print_tree(struct QTNode *parent, SDL_Renderer *renderer);
void qt_print_boundaries(struct QTNode *node);
struct Enemy *qt_query(struct QTNode *parent, SDL_FRect *r);

#endif