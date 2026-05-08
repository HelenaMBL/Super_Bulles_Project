#ifndef DONNEES_H
#define DONNEES_H

//Données globales du joueur et constantes du jeu

#define NIVEAU_MAX 3

/* Structure contenant toutes les informations persistantes
d’un joueur. Elle est utilisée dans les sauvegardes,
les paramètres et la progression du jeu. */

typedef struct {
    char pseudo[50];
    int niveau;
    int musiqueActive;
    int score;
    int tempsRestant;
    int coupsRestants;
} DonneesJoueur;

#endif