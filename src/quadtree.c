#include "quadtree.h"
#include "enemy.h"

enum QT_RESULT qt_add_node(struct QTNode *parent, struct Enemy *value) {
    char within_boundaries = qt_contains(&parent->boundary, &value->rect);
    if (!within_boundaries) {
        // Don't need to run this recursively if the enemy isn't within these
        // bounds.
        printf("NOT WITHIN BOUNDS (%f, %f, %f, %f)\n", parent->boundary.x,
               parent->boundary.y, parent->boundary.w, parent->boundary.h);
        return QT_VALUE_OUT_OF_BOUNDS;
    }

    if (parent->is_leaf) {
        // Parent is a leaf node
        if (parent->values_count < QT_NODE_CAPACITY) {
            // Add node to the current node and increment the capacity counter
            parent->values[parent->values_count++] = value;
            return QT_SUCCESS; // we're done since the element has been
                               // correctly inserted.
        } else {
            parent->is_leaf = 0;
            qt_subdivide(parent);

            parent->values_count = 0;

            for (size_t i = 0; i < QT_NODE_CAPACITY; ++i) {
                qt_add_node(parent, parent->values[i]);
            }

            // Call this function again. This time the parent will not be a leaf
            // node so subdivision will be skipped.
            return qt_add_node(parent, value);
        }
    } else {
        // If it isn't a leaf, need to identify which quadrant/s to go down.

        switch (qt_locate_quad(&parent->boundary, &value->rect)) {
        case 0b1000:
            return qt_add_node(parent->northwest, value);
            break;
        case 0b0100:
            return qt_add_node(parent->northeast, value);
            break;
        case 0b0010:
            return qt_add_node(parent->southeast, value);
            break;
        case 0b0001:
            return qt_add_node(parent->southwest, value);
            break;
        default:
            // None of the quadrants fully contain the value, so we add it to
            // the parent.
            if (parent->values_count < MAX_NODE_VALUES) {
                parent->values[parent->values_count++] = value;
                return QT_SUCCESS;
            } else {
                return QT_MAX_VALUES_OVERFLOW;
            }
        };
    }
}

enum QT_RESULT qt_subdivide(struct QTNode *parent) {
    // Create the quadrants and calculate their boundaries

    // Create northwest node.
    struct QTNode *northwest = calloc(1, sizeof(struct QTNode));

    northwest->values_count = 0;
    SDL_FRect northwest_boundary = {.x = parent->boundary.x,
                                    .y = parent->boundary.y,
                                    .w = parent->boundary.w / 2,
                                    .h = parent->boundary.h / 2};
    northwest->boundary = northwest_boundary;
    northwest->is_leaf = 1;
    parent->northwest = northwest;

    if (parent->northwest == NULL) {
        free(northwest);
        return QT_MEMORY_ERROR;
    }

    // Create northeast node
    struct QTNode *northeast = calloc(1, sizeof(struct QTNode));

    northeast->values_count = 0;
    SDL_FRect northeast_boundary = {
        .h = parent->boundary.h / 2,
        .w = parent->boundary.w / 2,
        // The x value is the parent's x value + half it's width
        .x = parent->boundary.x + (parent->boundary.w / 2),
        .y = parent->boundary.y};
    northeast->boundary = northeast_boundary;
    northeast->is_leaf = 1;
    parent->northeast = northeast;

    if (parent->northeast == NULL) {
        free(northeast);
        return QT_MEMORY_ERROR;
    }

    // Create southeast node.
    struct QTNode *southeast = calloc(1, sizeof(struct QTNode));

    southeast->values_count = 0;
    SDL_FRect southeast_boundary = {
        .h = parent->boundary.h / 2,
        .w = parent->boundary.w / 2,
        .x = parent->boundary.x + (parent->boundary.w / 2),
        .y = parent->boundary.y + (parent->boundary.h / 2)};
    southeast->boundary = southeast_boundary;
    southeast->is_leaf = 1;
    parent->southeast = southeast;

    if (parent->southeast == NULL) {
        free(southeast);
        return QT_MEMORY_ERROR;
    }
    // Create southwest node.
    struct QTNode *southwest = calloc(1, sizeof(struct QTNode));

    southwest->values_count = 0;
    SDL_FRect southwest_boundary = {.h = parent->boundary.h / 2,
                                    .w = parent->boundary.w / 2,
                                    .x = parent->boundary.x,
                                    .y = parent->boundary.y +
                                         (parent->boundary.h / 2)};
    southwest->boundary = southwest_boundary;
    southwest->is_leaf = 1;
    parent->southwest = southwest;

    if (parent->southwest == NULL) {
        free(southwest);
        return QT_MEMORY_ERROR;
    }

    return QT_SUCCESS;
}

int qt_contains(const SDL_FRect *boundary, const SDL_FRect *r) {
    // zero if it doesn't contain the rect, 1 if it does.
    float parent_x_mid = boundary->x + boundary->w / 2;
    float parent_y_mid = boundary->y + boundary->h / 2;

    // Ensure that there is overlap between the value and the parent in both
    // x and y directions.
    if (r->x + r->w < boundary->x || r->x > boundary->x + boundary->w) {
        return 0;
    }

    if (r->y + r->h < boundary->y || r->y > boundary->y + boundary->h) {
        return 0;
    }

    return 1;
}

char qt_locate_quad(const SDL_FRect *boundary, const SDL_FRect *r) {
    char possible_quadrant = 0b1111; // This number is represented in binary
    // 1 1 1 1 are the quadrants from northwest (MSB) going clockwise to
    // southwest (LSB)

    float parent_x_mid = boundary->x + boundary->w / 2;
    float parent_y_mid = boundary->y + boundary->h / 2;

    if (r->x > parent_x_mid) {
        // Value is completely in the east quadrants mask out bit 4
        // (MSB) and bit 1(LSB)
        possible_quadrant &= 0b0110;
    } else if (r->x + r->w < parent_x_mid) {
        // Value is completely in the west quadrants mask out bit 2 and
        // 3
        possible_quadrant &= 0b1001;
    } else {
        // Value spans multiple quadrants in the y direction. There's no
        // child that contains it.
        return 0;
    }

    if (r->y + r->h < parent_y_mid) {
        // Value is completely above the parent y midpoint, mask out the
        // the southern quadrants
        possible_quadrant &= 0b1100;
    } else if (r->y > parent_y_mid) {
        // The enemy is completely below the parent y midpoint, mask out
        // the northern quadrants
        possible_quadrant &= 0b0011;
    } else {
        // Value spans multiple quadrants in the y direction. There's no
        // child that contains it.
        return 0;
    }

    return possible_quadrant;
}

void qt_initialize(struct QTNode *parent, float width, float height) {

    SDL_FRect boundary = {
        .x = 0,
        .y = 0,
        .w = width,
        .h = height,
    };

    parent->boundary = boundary;

    parent->northeast = NULL;
    parent->northwest = NULL;
    parent->southwest = NULL;
    parent->southeast = NULL;

    parent->values_count = 0;
    parent->is_leaf = 1;
}

void qt_free(struct QTNode *parent) {
    if (parent == NULL) {
        return;
    }

    qt_free(parent->northeast);
    qt_free(parent->northwest);
    qt_free(parent->southeast);
    qt_free(parent->southwest);

    SDL_free(parent);
    parent = NULL;
}

void qt_print_tree(const struct QTNode *parent, SDL_Renderer *renderer) {
    if (parent == NULL) {
        return;
    }

    printf("\nPrinting node:\n");
    printf("\tLeaf Node: %i\n", parent->is_leaf);
    printf("\tBoundary: (%f, %f, %f, %f)\n", parent->boundary.x,
           parent->boundary.y, parent->boundary.x + parent->boundary.w,
           parent->boundary.y + parent->boundary.h);

    printf("\tValues:\n");
    if (parent->values_count) {
        if (renderer != NULL) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderRect(renderer, &parent->boundary);
        }
        for (size_t i = 0; i < parent->values_count; i++) {
            printf("\t\tValue: x = %f, y = %f\n", parent->values[i]->x,
                   parent->values[i]->y);
        }
    } else {
        printf("\t\tNo values\n");
    }

    qt_print_tree(parent->northwest, renderer);
    qt_print_tree(parent->northeast, renderer);
    qt_print_tree(parent->southeast, renderer);
    qt_print_tree(parent->southwest, renderer);
}

void qt_print_boundaries(const struct QTNode *node) {
    printf("(x=%f, y=%f, w=%f, h=%f, is_leaf=%i, values_count=%i)",
           node->boundary.x, node->boundary.y, node->boundary.w,
           node->boundary.h, node->is_leaf, node->values_count);
}