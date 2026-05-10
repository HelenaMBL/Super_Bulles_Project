//
// Created by helen on 10/05/2026.
//

#include <stdio.h>
#include "sauvegarde.h"
#include "constantes.h"



void enregistrer(Partie* p, Objet *joueur) {
    char nomfichier[60];
    FILE* pf;
    snprintf(nomfichier, sizeof(nomfichier), "sauvegarde/%s.txt", p->pseudo);
    pf = fopen(nomfichier, "w");

    if (!pf) {
        perror("fopen a échoué");
        printf("Nom fichier = [%s]\n", nomfichier);
        return;
    }



    if (fprintf(pf, "%s;%d;%f;%d;%d;%d;%d;%d;%d;%d;%d", p->pseudo, p->vie, p->temps,p->niveau,joueur->x,joueur->y,p->score) < 0) {//joueur->dx,joueur->dy,joueur->tx,joueur->ty,p->score) < 0) {
        perror(RED"Erreur écriture fichier"RESET);
        fclose(pf);
        return ;
    }
    printf(GREEN"enregistrement de %s termine !", nomfichier);
    fclose(pf);
}