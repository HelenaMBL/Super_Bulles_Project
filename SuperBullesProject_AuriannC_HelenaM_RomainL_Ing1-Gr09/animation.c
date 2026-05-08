//
// Created by helen on 29/04/2026.
//

#include <stdio.h>
#include <allegro.h>
#include <allegro/gfx.h>
#include <allegro/system.h>
#include "animation.h"

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

void load_AnimStruct(AnimationMa* p, int nbrimages, char* pathfichier) {
    p->nbrFrames=nbrimages;
    p->images=malloc(sizeof(BITMAP *) * nbrimages);
    load_Anim(nbrimages, pathfichier, p->images);
}




#define FRAME_DURATION 80
#define DELTA_X 14
// Séquence d'animation
#define NIMAGE 14
#define IMAGESTAT 7


#if 0
clock_t diffMilliseconds(clock_t end, clock_t start) {
    return (end - start) * 1000 / CLOCKS_PER_SEC;
}

void deplacement_Warrior () {
    install_mouse();
    char decorPath[1024];
    // Données géométriques de l'animation
    int x,y;
    int dx,dy;
    int tx,ty;


    // Pour pouvoir avancer très lentement on avance moins souvent
    //  ( ajouter dx une fois tous les tmpdx, initialement à chaque fois )
    int tmpdx=14;

    // Gestion de l'enchainement des images de la séquence
    // indice de l'image courante
    int imgcourante=0;
    // on passe à l'image suivante une fois tous les tmpimg
    int cptimg=0, tmpimg=7;

    // Séquence d'animation
    BITMAP* animMarche[NIMAGE];
    BITMAP* animStat[IMAGESTAT];


    // La tempo générale (fonction rest) sera réglable
    int tempoglobale=10;

    sprintf(decorPath, "../images/decorbis%s-24.bmp", (USE_FULLSCREEN) ? "1280x800" : "800x600");

    BITMAP *decor = load_bitmap(decorPath, NULL);
    if (!decor) {
        allegro_message("Echec chargement bitmap '%s' [%s]", decorPath, allegro_error);
        exit(EXIT_FAILURE);
    }

    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    load_Anim(NIMAGE,"../SpritesAnimation/deplacement/Warrior%d.bmp", animMarche);
    load_Anim(IMAGESTAT,"../SpritesAnimation/WarriorStatique/WarriorStat%d.bmp", animStat);

    // initialisation des données du personnage zelda

    tx = animMarche[0]->h; // pour la taille on se base sur la 1ère image de la séquence
    ty = animMarche[0]->w;
    x = 0;
    y = SCREEN_W/2-tx;
    //dx = 10;
    dy = 0;

    clock_t  lastClock = 0;
    clock_t  currentClock;
    BITMAP* Bulle_Niv1 = load_bitmap("../SpritesAnimation/BulleNiv1.bmp", NULL);
    //Bulle b;
    //jeu(&page,&decor, &animMarche, &animStat);

    //jeu(&page, &decor); // appel de ta fonction
    while (!key[KEY_ESC]) {

        currentClock = clock();

        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // appel d'un sous programme de réglage interactif des parametres
        // ( seulement utile sur cet exemple ou pour du debug )
        //reglages(page,&tempoglobale,&dx,&tmpdx,&tmpimg);

        // gestion enchainement des images
        // incrémenter imgcourante une fois sur tmpimg
        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50; // limite pour éviter blocage

        //textprintf_ex(page,font,16,60,makecol(255,255,255),0,"DIF time : DIF time = %f",difftime(currentTime,lastTime) *1000);
        if (key [KEY_RIGHT]) {
            dx = DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (x+tx>SCREEN_W)
                    dx = 0;
                x+=dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        }

        if (key[KEY_LEFT]) {
            dx = -DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (x<=0)
                    dx = 0;
                x+=dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        } else if (!key[KEY_RIGHT] && !key[KEY_LEFT]) {
            dx=0;
            if (diffMilliseconds(currentClock, lastClock) >=300) {
                lastClock = currentClock;
                imgcourante = (imgcourante + 1) % IMAGESTAT;
            }
        }

        // afficher l'image courante du chat (selon le sens...)
        if (dx>0) {
            draw_sprite(page,animMarche[imgcourante],x,y);
        }
        else if (dx<0) {
            draw_sprite_h_flip(page,animMarche[imgcourante],x,y);
        }
        else if (dx==0) {
            draw_sprite(page,animStat[imgcourante],x,y);
        }
        // affichage du buffer à l'écran
        textprintf_ex(page,font,10,10,makecol(255,255,255),0,
"animMarche=%d cptimg=%d tmpimg=%d",imgcourante,cptimg,tmpimg);
        //blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        //rest(tempoglobale);

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }
}



void deplacement_Bulles(Bulle *b) {

    if (b->x > SCREEN_W / 2) {

        int choix = rand() % 2 +1;

        if (choix == 1) {
            // diagonale gauche (retour centre)
            b->vx = -1;
            b->vy = 2;
        }
        else if (choix == 2) {
            // légère droite
            b->vx = 1;
            b->vy = 2;
        }
        else {
            b->vx = 0;


        }


    }
}

void jeu(BITMAP *page, BITMAP* decor,  BITMAP *animMarche[],
          BITMAP *animStat[]) {
    BITMAP* Bulle_Niv1 = load_bitmap("../SpritesAnimation/BulleNiv1.bmp", NULL);
    //srand(time(NULL));

    Bulle b;

    // SPAWN INITIAL
    b.x = rand() % SCREEN_W;
    b.y = 0;
    //b.t = 0;

    deplacement_Bulles(&b);
    blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    // UPDATE POSITION
    b.x += b.vx;
    b.y += b.vy;

    // b.x += (int)(3 * sin(b.t));

    draw_sprite(page, Bulle_Niv1, b.x, b.y);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

}
#endif




