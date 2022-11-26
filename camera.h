static const char ROW_CHAR = '-';
static const char COL_CHAR = '|';
static const char CORNER_CHAR = '+';
const int CAMERA_PADDING[2] = {2, 4};

typedef struct camera {
    // border thing
    int height;
    int width;
    const int *padding;

    // content
    char *map;

} Camera;
