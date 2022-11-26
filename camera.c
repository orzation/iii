#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef __linux__
#include <sys/ioctl.h>
#elif _WIN32
// todo
#endif /* system */


#include "camera.h"




/* 获取窗口宽高 */
void getWindowSize(int *h, int *w) {
    #ifdef __linux__
        struct winsize max;
        ioctl(0, TIOCGWINSZ, &max);
        *h =  max.ws_row, *w = max.ws_col;
    #elif _WIN32
    // todo
    #endif
}

/* 相机 */
inline int pos(const Camera *c, const int x, const int y) {
    return (c->padding[0] + y) * c->width + c->width + x - 1;
}

void display(const Camera *c) {
    /* system("clear"); */
    printf("%s", c->map);
}

void drawBorder(const Camera *c) {
    const int ch = c->height, cw = c->width, tp = c->padding[0], lp = c->padding[1];
    const int dhp = ch - tp, dwp = cw - lp;

    memset(c->map, ' ', c->height * c->width);
    for (int i = lp; i < dwp; ++ i)
        c->map[tp * cw + i] = c->map[(dhp - 1) * cw + i] = ROW_CHAR;
    for (int i = tp; i < dhp ; ++ i)
        c->map[i * cw + lp] = c->map[i * cw + dwp - 1] = COL_CHAR;
    for (int i = 0; i < ch - 1; i ++)
        c->map[i * cw + cw - 1] = '\n';
    c->map[tp * cw + lp]
        = c->map[tp * cw + dwp - 1]
        = c->map[(dhp - 1) * cw + lp]
        = c->map[(dhp - 1) * cw + dwp - 1]
        = CORNER_CHAR;
    c->map[( ch - 1 ) * cw] = 0;
}

void drawContent(const Camera *c, const char *ctx[]) {
    // todo

}

Camera* initCamera() {
    Camera *c = (Camera*)malloc(sizeof(Camera));
    getWindowSize(&c->height, &c->width);
    c->map =  (char*)malloc(sizeof(char) * c->height * c->width);
    c->padding = CAMERA_PADDING;

    drawBorder(c);
    return c;
}

void cleanCamera(Camera *c) {
    free(c->map), free(c);
}

void updateCamera(Camera *c, const char *ctx[]) {
    int h, w;
    getWindowSize(&h, &w);
    if (h != c->height || w != c->width) {
        c->height = h, c->width = w;
        drawBorder(c);
    }
    if (ctx != NULL) drawContent(c, ctx);
}

int main (int argc, char *argv[]) {
    Camera *came = initCamera();
    while(1) {
        updateCamera(came, NULL);
        display(came);
        usleep(30000);
    }
    cleanCamera(came);

    return 1; /* unreachable */
}
