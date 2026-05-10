//
// Created by helen on 10/05/2026.
//

#include "partie.h"
#include <stdio.h>
#include "constantes.h"


void lire(Partie* p, Objet *joueur) {
    char nomfichier[60];
    snprintf(nomfichier, sizeof(nomfichier), "sauvegarde/%s.txt", p->pseudo);

    FILE* pf = fopen(nomfichier, "r");
    if (!pf) {
        printf(YELLOW"Fichier inexistant -> création de %s\n" RESET,nomfichier);
        return;
    }

    int ok = fscanf(pf,
        //"%39[^;];%d;%f;%d;%d;%d;%d;%d;%d;%d;%d",
        "%39[^;];%d;%f;%d;%d;%d;%d",
        p->pseudo,
        &p->vie,
        &p->temps,
        &p->niveau,
        &joueur->x,
        &joueur->y,
       /*
        &joueur->dx,
        &joueur->dy,
        &joueur->tx,
        &joueur->ty, */
        &p->score
    );


    if (ok != 11) {
        perror(RED "Fichier corrompu: %s\n"RESET);
    }
    perror(nomfichier);
    printf(GREEN"%s a ete lu avec succes !\n"RESET, nomfichier);


    fclose(pf);
}

void Parties(Partie* partie, Objet* joueur){


    partie->temps=120;
    partie->vie=3;
    partie->niveau=1;
    partie->score=0;
    //jouer(partie,joueur); // nouvelle partie

}