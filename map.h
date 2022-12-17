#include <stdint.h>

typedef struct map Map;

/* 写了 init 相关代码后记得移动到.c文件 */
struct map {
    /* size */
    uint16_t height;
    uint16_t width;
    /* content */
    char **data;
};

char getMapCh(const Map *m, const uint16_t y, const uint16_t x);
uint16_t getMapH(const Map *m);
uint16_t getMapW(const Map *m);
