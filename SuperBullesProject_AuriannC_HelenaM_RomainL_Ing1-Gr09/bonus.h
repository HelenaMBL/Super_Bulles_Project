//
// Created by helen on 10/05/2026.
//

#ifndef SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_BONUS_H
#define SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_BONUS_H

typedef enum {
    BONUS_TIR_RAPIDE,
    BONUS_MOVE_RAPIDE,
    NB_TYPES_BONUS
} TypeBonus;

typedef struct {
    float x, y;
    float vy;         // tombe vers le bas
    int actif;
    TypeBonus type;
} Bonus;





#endif //SUPERBULLESPROJECT_AURIANNC_HELENAM_ROMAINL_ING1_GR09_BONUS_H
