#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include "animation.h"

typedef struct {
    int x;
    int y;
    int vx;
    int vy;
    bool flip;
    Animation* animation;
} Objet;

void deplacement_Bulle(Objet *bulle);
void draw_objectSprite(Objet *p, BITMAP* page);


#endif //OBJECT_H
