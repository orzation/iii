

#include "map.h"
#include <stdint.h>


char getMapCh(const Map *m, const uint16_t y, const uint16_t x) {
    return m->data[y][x];
}

uint16_t getMapH(const Map *m) {
    return m->height;
}

uint16_t getMapW(const Map *m) {
    return m->width;
}
