#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro/gfx.h>

typedef struct {
    int nbrFrames;
    int currentFrame;
    int offsetX, offsetY;
    BITMAP** images; //tableau de bitmaps(pointeurs)
} Animation;


void load_bitmaps(int nbrimages,char* pathfichier ,BITMAP *tab[nbrimages]);
void load_Anim(Animation* p, int nbrimages, char* pathfichier);
void increment_Anim(Animation* p);

void jeu();
#endif //ANIMATION_H
