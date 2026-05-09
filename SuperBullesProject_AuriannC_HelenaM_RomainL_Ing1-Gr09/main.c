#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include "object.h"

#define USE_FULLSCREEN 1
//#define USE_FULLSCREEN 0
#define APP_CARD (USE_FULLSCREEN ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED)
#define APP_SCREEN_W (USE_FULLSCREEN ? 1280 : 800)
#define APP_SCREEN_H (USE_FULLSCREEN ? 800 : 600)

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

#define FRAME_DURATION 80
#define DELTA_X 14
// Sous programme pour jouer avec les parametres
void reglages(BITMAP *bmp,int *ptempoglobale,int *pdx,int *ptmpdx,int *ptmpimg) {
    textprintf_ex(bmp,font,16,20,makecol(255,255,255),0,"F1 - F2 : tempoglobale = %d",*ptempoglobale);
    textprintf_ex(bmp,font,16,30,makecol(255,255,255),0,"F3 - F4 :           dx = %d",*pdx);
    textprintf_ex(bmp,font,16,40,makecol(255,255,255),0,"F5 - F6 :        tmpdx = %d",*ptmpdx);
    textprintf_ex(bmp,font,16,50,makecol(255,255,255),0,"F7 - F8 :       tmpimg = %d",*ptmpimg);


    if (key[KEY_F1]) (*ptempoglobale)--;
    if (*ptempoglobale<0) *ptempoglobale=0;
    if (key[KEY_F2]) (*ptempoglobale)++;
    if (*ptempoglobale>100) *ptempoglobale=100;

    if ( (key[KEY_F3] && *pdx>0) || (key[KEY_F4] && *pdx<0) ) (*pdx)--;
    //if ( (key[KEY_LEFT] && *pdx>0) || (key[KEY_F4] && *pdx<0) ) (*pdx)--;
    if ( (key[KEY_F4] && *pdx>0) || (key[KEY_F3] && *pdx<0) ) (*pdx)++;
    //if ( (key[KEY_RIGHT] && *pdx>0) || (key[KEY_F3] && *pdx<0) ) (*pdx)++;
    if ( key[KEY_RIGHT] && *pdx==0 ) (*pdx)++;

    if (key[KEY_F5]) (*ptmpdx)--;
    if (*ptmpdx<1) *ptmpdx=1;
    if (key[KEY_F6]) (*ptmpdx)++;
    if (*ptmpdx>100) *ptmpdx=100;

    if (key[KEY_F7]) (*ptmpimg)--;
    if (*ptmpimg<1) *ptmpimg=1;
    if (key[KEY_F8]) (*ptmpimg)++;
    if (*ptmpimg>100) *ptmpimg=100;

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
    Animation decorAnim;
    Animation marcheAnim;
    Animation attendAnim;
    Animation bulleAnim;
    Animation tirAnim;

    Objet decor = {0};
    Objet warrior = {0};
    Objet bulle = {0};
    Objet tir = {0};

    decor.animation = &decorAnim;
    warrior.animation = &attendAnim;
    bulle.animation = &bulleAnim;
    tir.animation = &tirAnim;

    bulle.x = rand() % SCREEN_W;
    bulle.y = 0;

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

    init_bulle_big(&bulle, &bulleAnim, 0, SCREEN_W/2-tx);

    bulle.y = 0;
    bulle.x=rand()%SCREEN_W;
    bulle.vy = 0;
    bulle.vx = 0; // entre -2 et 2
    if (bulle.vx == 0) bulle.vx = 1; // évite vx nul

    while (!key[KEY_ESC]) {
        currentClock = clock();

        blit(decorAnim.images[0],page,0,0,0,0,SCREEN_W,SCREEN_H);
        reglages(page,&tempoglobale,&dx,&tmpdx,&tmpimg);
        
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

            increment_Anim(&decorAnim);
            increment_Anim(&marcheAnim);
            increment_Anim(&attendAnim);
            increment_Anim(&bulleAnim);
            lastClock = currentClock;
        }

        // afficher l'image courante du chat (selon le sens...)
        if (dx>0) {
            warrior.flip = false;
            warrior.animation = &marcheAnim;
            //draw_sprite(page,marcheAnim.images[imgcourante],x,y);
        }
        else if (dx<0) {
            warrior.flip = true;
            warrior.animation = &marcheAnim;
        }
        else if (dx==0) {
            warrior.animation = &attendAnim;
        }

        deplacement_Bulle(&bulle);

        draw_objectSprite(&decor, page);
        draw_objectSprite(&warrior, page);
        draw_objectSprite(&bulle, page);

        if (key[KEY_SPACE]) {
            draw_objectSprite(&tir, page);
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }




    destroy_bitmap(page);
    destroy_bitmap(decorAnim.images[0]);
    allegro_exit();
    return 0;
}
END_OF_MAIN()