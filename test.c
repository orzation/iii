#include <stdio.h>
#include "camera.h"
#include "map.h"
#include <stdlib.h>

#ifdef __linux__
#include <termio.h>
#elif _WIN32
// todo
#endif

int getKey(){
    int in;

#ifdef __linux__
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
    
    in = getchar();
    
    tcsetattr(0,TCSANOW,&stored_settings);
#elif _WIN32
    // todo
#endif
    return in;
}


int main (int argc, char *argv[]) {
    FILE *f = fopen("./test.txt", "r");
    const int h = 70, w = 140;
    char **g = (char **)malloc(sizeof(char*) * h);
    for (int i = 0; i < h; i ++) g[i] = (char *)malloc(w);

    for (int i = 0; i < h; i ++)
        for (int j = 0; j < w; j ++)
            g[i][j] = fgetc(f);

    Map m = {h, w, g};
    
    int x = 0, y = 0;
    while (1) {
        updateCamera(getCamera(), y, x, &m);
        char op = getKey();
        if (op == 'h') x--;
        if (op == 'i') x++;
        if (op == 'n') y++;
        if (op == 'e') y--;
    }
    cleanCamera(getCamera());
    return 1;
}
