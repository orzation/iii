#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/* system */
#ifdef __linux__
#include <sys/ioctl.h>
#elif _WIN32
// todo
#endif

#include "camera.h"
#include "map.h"
#include "utils.h"

static const char NIL_CHAR = '`';
static const char ROW_CHAR = '-';
static const char COL_CHAR = '|';
static const char CORNER_CHAR = '+';
static const uint16_t PADDING[2] = {2, 4};
static const uint16_t SLEEP_TIME = 30000; /* us */

struct camera {
    /* position */
    int16_t posY;
    int16_t posX;
    /* border */
    uint16_t height;
    uint16_t width;
    /* string content (1d) */
    char *view;
};

/* hunger single instance */
static Camera* instance;

/* system: get console char size */
static void getWindowSize(uint16_t *h, uint16_t *w) {
    #ifdef __linux__
        struct winsize max;
        ioctl(0, TIOCGWINSZ, &max);
        *h =  max.ws_row, *w = max.ws_col;
    #elif _WIN32
        // todo
    #endif
}

static inline uint32_t pos(const Camera *c, const int y, const int x) {
    return (PADDING[0] + y) * c->width + PADDING[1] + x;
}

static inline void display() {
    /* system("clear"); */
    // todo color
    printf("%s", instance->view);
    usleep(SLEEP_TIME);
}

static void drawBorder(const Camera *c) {
    const uint16_t ch = c->height, cw = c->width,
        rh = ch - (PADDING[0] << 1), rw = cw - (PADDING[1] << 1);
    memset(c->view, ' ', ch * cw);

    /* draw char */
    for (uint16_t i = 0; i < rw; ++ i)
        c->view[pos(c, 0, i)] = c->view[pos(c, rh - 1, i)] = ROW_CHAR;
    for (uint16_t i = 0; i < rh ; ++ i)
        c->view[pos(c, i, 0)] = c->view[pos(c, i, rw - 1)] = COL_CHAR;
    c->view[pos(c, 0, 0)]
        = c->view[pos(c, 0, rw - 1)]
        = c->view[pos(c, rh - 1, 0)]
        = c->view[pos(c, rh - 1, rw - 1)]
        = CORNER_CHAR;

    /* fix line */
    for (uint16_t i = 0; i < ch - 1; ++ i)
        c->view[i * cw + cw - 1] = '\n';
    /* final end */
    c->view[( ch - 1 ) * cw] = 0;
}

static void projectMap2Content(const Camera *c, const Map *m) { 
    const int16_t y = c->posY, x = c->posX;
    const uint16_t rh = c->height - (PADDING[0] << 1) , rw = c->width - (PADDING[1] << 1),
        /* content size = border size - 2*/
        rch = rh - 2, rcw = rw - 2,
        mh = m->height, mw = m->width, 
        /* cross block position */
        py1 = y < 0 ? -y : 0, px1 = x < 0 ? -x : 0,
        py2 = MIN(mh, rch + y) - y, px2 = MIN(mw, rcw + x) - x;
    char ct[rch][rcw];

    /* init unreachable content char */
    memset(ct, NIL_CHAR, rch * rcw);

    printf("%d %d\n", x, y);
    /* cut a map block */
    for (uint16_t i = py1; i < py2; ++ i)
        for (uint16_t j = px1; j < px2; ++ j)
            ct[i][j] =  m->data[i+y][j+x];

    /* draw view */
    for (uint16_t i = 0; i < rch; ++ i)
        for (uint16_t j = 0; j < rcw; ++ j)
            c->view[pos(c, i + 1, j + 1)] = ct[i][j];
}

static Camera* initCamera() {
    Camera *c = (Camera*)malloc(sizeof(Camera));
    getWindowSize(&c->height, &c->width);
    c->view =  (char*)malloc(c->height * c->width);
    drawBorder(c);
    return c;
}

Camera* getCamera() {
    if (instance != NULL) return instance;
    instance = initCamera();
    return instance;
}

void cleanCamera(Camera *c) {
    free(c->view), free(c);
}

void updateCamera(Camera *c, const int16_t y, const int16_t x, const Map *m) {
    uint16_t h, w;
    getWindowSize(&h, &w);
    
    if (h != c->height || w != c->width) {
        c->height = h, c->width = w;
        drawBorder(c);
    }
    
    c->posY = y, c->posX = x; 
    if (m != NULL) projectMap2Content(c, m);
    display();
}
