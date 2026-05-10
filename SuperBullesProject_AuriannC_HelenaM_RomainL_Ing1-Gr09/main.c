#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include "object.h"
#include "reglages.h"
#include "constantes.h"


void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(APP_CARD, APP_SCREEN_W, APP_SCREEN_H, 0, 0) != 0)
    {
        allegro_message("%s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

clock_t diffMilliseconds(clock_t end, clock_t start) {
    return (end - start) * 1000 / CLOCKS_PER_SEC;
}


int main()
{
    srand((unsigned int)time(NULL) ^ (unsigned int)clock());

    initialisation_allegro();
    install_mouse();
    char decorPath[1024];
    // Données géométriques de l'animation
    int dx,dy;
    int tx,ty;


    // Pour pouvoir avancer très lentement on avance moins souvent
    //  ( ajouter dx une fois tous les tmpdx, initialement à chaque fois )
    int tmpdx=14;

    // Gestion de l'enchainement des images de la séquence
    // indice de l'image courante
    int imgcourante=0;
    int imgcouranteStat=0;
    // on passe à l'image suivante une fois tous les tmpimg
    int cptimg=0, tmpimg=7;

    // Séquence d'animation de chargement
    Animation decorAnim = {0};
    Animation marcheAnim = {0};
    Animation attendAnim = {0};
    Animation bulleAnim = {0};
    Animation tirAnim = {0};
    tirAnim.offsetY=-72;
    Animation* animations[] = {
        &decorAnim,
        &marcheAnim,
        &attendAnim,
        &bulleAnim,
        &tirAnim
    };

    Objet decor = {0};
    Objet warrior = {0};
    Objet bulle1 = {0};
    Objet bulle2 = {0};
    Objet bulle3 = {0};

    Objet* objects[] = {
        &decor,
        &warrior,
        &bulle1,
        &bulle2,
        &bulle3,
    };

    decor.animation = &decorAnim;
    warrior.animation = &attendAnim;
    bulle1.animation = &bulleAnim;
    bulle2.animation = &bulleAnim;
    bulle3.animation = &bulleAnim;

    Partie partie = {0};

    // La tempo générale (fonction rest) sera réglable
    int tempoglobale=10;

    sprintf(decorPath, "../images/decorbis%s-24.bmp", (USE_FULLSCREEN) ? "1280x800" : "800x600");

    load_Anim(&decorAnim, 1, decorPath);
    load_Anim(&marcheAnim, 14, "../SpritesAnimation/deplacement/Warrior%d.bmp");
    load_Anim(&attendAnim,7, "../SpritesAnimation/WarriorStatique/WarriorStat%d.bmp");
    load_Anim(&bulleAnim,1, "../SpritesAnimation/BulleNiv1.bmp");
    load_Anim(&tirAnim,1, "../SpritesAnimation/tirWarrior.bmp");

    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    draw_objectSprite(&decor, page);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    tx = marcheAnim.images[0]->h; // pour la taille on se base sur la 1ère image de la séquence
    warrior.y = SCREEN_W/2-tx;

    clock_t  lastClock = 0;
    clock_t  currentClock;

    init_bulle_big(&bulle1, &bulleAnim, 0, SCREEN_W/2-tx);
    init_bulle_big(&bulle2, &bulleAnim, 0, SCREEN_W/2-tx);
    init_bulle_big(&bulle3, &bulleAnim, 0, SCREEN_W/2-tx);

    bulle1.x=rand()%SCREEN_W;
    if (bulle1.vx == 0) bulle1.vx = 1; // évite vx nul
    bulle2.x=rand()%SCREEN_W;
    if (bulle2.vx == 0) bulle2.vx = 1; // évite vx nul
    bulle3.x=rand()%SCREEN_W;
    if (bulle3.vx == 0) bulle3.vx = 1; // évite vx nul

    while (!key[KEY_ESC]) {
        currentClock = clock();

        blit(decorAnim.images[0],page,0,0,0,0,SCREEN_W,SCREEN_H);
        affichageData(page,&partie); // ,&dx,&tmpdx,&tmpimg);
        
        // incrémenter imgcourante une fois sur tmpimg
        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50; // limite pour éviter blocage

        bool changeFrame = diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION;

        if (key [KEY_RIGHT]) {
            dx = DELTA_X;
            if (changeFrame){
                if (warrior.x+tx>SCREEN_W)
                    dx = 0;
            }
        }
        if (key[KEY_LEFT]) {
            dx = -DELTA_X;
            if (changeFrame){
                if (warrior.x<=0)
                    dx = 0;
            }
        } else if (!key[KEY_RIGHT] && !key[KEY_LEFT]) {
            dx=0;
        }
        if (changeFrame){
            warrior.x+=dx;

            for (int cpt = 0; cpt < ARRAY_COUNT(animations); cpt++) {
                increment_Anim(animations[cpt]);
            }
            //increment_Anim(&decorAnim);
            //increment_Anim(&marcheAnim);
            //increment_Anim(&attendAnim);
            //increment_Anim(&bulleAnim);
            lastClock = currentClock;
        }

        // afficher l'image courante du chat (selon le sens...)
        if (dx>0) {
            warrior.flip = false;
            warrior.animation = &marcheAnim;
        }
        else if (dx<0) {
            warrior.flip = true;
            warrior.animation = &marcheAnim;
        }
        else if (dx==0) {
            warrior.animation = &attendAnim;
        }
        if (key[KEY_SPACE]) {

            warrior.animation = &tirAnim;
        }

        deplacement_Bulle(&bulle1);
        deplacement_Bulle(&bulle2);
        deplacement_Bulle(&bulle3);


        for (int cpt = 0; cpt < ARRAY_COUNT(objects); cpt++) {
            draw_objectSprite(objects[cpt], page);
        }
        //draw_objectSprite(&decor, page);
        //draw_objectSprite(&warrior, page);
        //draw_objectSprite(&bulle, page);


        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }




    destroy_bitmap(page);
    for (int cpt = 0; cpt < ARRAY_COUNT(animations); cpt++) {
        destroy_bitmap(animations[cpt]->images[0]);
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()