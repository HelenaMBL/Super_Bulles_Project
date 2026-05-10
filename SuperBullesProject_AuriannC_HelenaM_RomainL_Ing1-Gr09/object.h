#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include "animation.h"

typedef enum
{
    BULLE_BIG,
    BULLE_SMALL,
    EXPLOSION
} ObjectType;

typedef struct
{
    const char* name;
    int x;
    int y;
    int vx;
    int vy;
    int radius;

    bool hidden;
    bool flip;

    ObjectType type;

    Animation* animation;

} Objet;

void deplacement_Objet(Objet *p);
void draw_objectSprite(Objet *p, BITMAP* page);
void init_bulle_big(Objet* bulle, Animation* anim, int x, int y);
void split_bulle(Objet* big, Objet* small, Animation* smallAnim);
int collision_bulle_tir(Objet* bulle, int tirX, int tirY);


#endif //OBJECT_H
