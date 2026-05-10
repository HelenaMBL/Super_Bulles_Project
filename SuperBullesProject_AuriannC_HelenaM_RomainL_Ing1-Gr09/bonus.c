//
// Created by helen on 10/05/2026.
//

#include "bonus.h"
#include "constantes.h"
#include <stdlib.h>
#include "allegro.h"

void spawn_bonus(Bonus *bonus_map, float x, float y)
{
    for(int i = 0; i < MAX_BONUS; i++){
        if(!bonus_map[i].actif){
            bonus_map[i].x     = x;
            bonus_map[i].y     = y;
            bonus_map[i].vy    = 2.0f;
            bonus_map[i].type  = rand() % NB_TYPES_BONUS;
            bonus_map[i].actif = 1;
            return;
        }
    }
}

void draw_bonus(BITMAP *page, Bonus *b)
{
    if(!b->actif) return;

    int couleur = (b->type == BONUS_TIR_RAPIDE)
                  ? makecol(255, 220, 0)    // jaune  = tir rapide
                  : makecol(0,   220, 100); // vert   = déplacement rapide

    rectfill(page,
             (int)b->x - 10, (int)b->y - 10,
             (int)b->x + 10, (int)b->y + 10,
             couleur);

    // lettre indicatrice
    const char *label = (b->type == BONUS_TIR_RAPIDE) ? "T" : "M";
    textout_ex(page, font, label,
               (int)b->x - 3, (int)b->y - 4,
               makecol(0,0,0), -1);
}