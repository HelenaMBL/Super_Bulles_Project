//
// Created by helen on 29/04/2026.
//

#ifndef PICTURE_ANIMATION_H
#define PICTURE_ANIMATION_H

#endif //PICTURE_ANIMATION_H

typedef struct {
    int nbrFrames;
    BITMAP** images; //taleau de bitmaps(pointeurs)
} AnimationMa;


void load_Anim(int nbrimages,char* pathfichier ,BITMAP *tab[nbrimages]);
void load_AnimStruct(AnimationMa* p, int nbrimages, char* pathfichier);

typedef struct {
    int x;
    int y;
    int vx;
    int vy;
} Bulle;






void deplacement_Bulles(Bulle *b);

void jeu();