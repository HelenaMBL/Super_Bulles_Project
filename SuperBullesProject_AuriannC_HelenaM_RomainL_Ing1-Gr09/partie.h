//
// Created by helen on 10/05/2026.
//

#ifndef SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_PARTIE_H
#define SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_PARTIE_H
#include "object.h"

typedef struct{
    char pseudo[40];
    int vie;
    float temps;
    int niveau;
    int score;
}Partie	;

void lire(Partie* p, Objet *j);



#endif //SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_PARTIE_H
