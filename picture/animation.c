//
// Created by helen on 29/04/2026.
//

#include <stdio.h>
#include <allegro.h>
#include <allegro/gfx.h>
#include <allegro/system.h>

void load_Anim(int nbrimages,char* pathfichier, BITMAP *tab[nbrimages]) {
    // charger les images de la séquence d'animation

    for (int i=0;i<nbrimages;i++)
    {
        char nomfichier[256];
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,pathfichier,i);

        tab[i] = load_bitmap(nomfichier,NULL);
        if (!tab[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }

}
