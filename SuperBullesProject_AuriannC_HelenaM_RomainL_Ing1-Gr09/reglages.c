//
// Created by helen on 10/05/2026.
//

#include "reglages.h"
#include <allegro.h>

void affichageData(BITMAP *bmp, Partie *p){ //, int timer_tir, int timer_move)

    textprintf_ex(bmp,font,16,20,makecol(255,255,255),0,"Niveau : %d", p->niveau);
    textprintf_ex(bmp,font,16,30,makecol(255,255,255),0,"Vie : %d",p->vie);
    textprintf_ex(bmp,font,16,40,makecol(255,255,255),0,"Temps : %f",p->temps);
    textprintf_ex(bmp,font,16,50,makecol(255,255,255),0,"score : %d",p->score);
    /*
    if(timer_tir > 0)
        textprintf_ex(bmp, font, 16, 60, makecol(255,220,0), 0,
                      "TIR RAPIDE : %ds", timer_tir / 60);
    if(timer_move > 0)
        textprintf_ex(bmp, font, 16, 70, makecol(0,220,100), 0,
                      "MOVE+ : %ds", timer_move / 60);
                      */

}