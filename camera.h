#include <stdint.h>

typedef struct map Map;
typedef struct camera Camera;

Camera* getCamera();
void cleanCamera(Camera *c);
void updateCamera(Camera *c, const int16_t y, const int16_t x, const Map *m);
