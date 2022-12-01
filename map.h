#include <stdint.h>

typedef struct map {
    /* size */
    int16_t height;
    int16_t width;
    /* content */
    char **data;
} Map;
