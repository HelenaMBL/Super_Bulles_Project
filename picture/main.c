#include <stdio.h>
#include <allegro.h>

#define USE_FULLSCREEN 1
//#define USE_FULLSCREEN 0
#define APP_CARD (USE_FULLSCREEN ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED)
#define APP_SCREEN_W (USE_FULLSCREEN ? 1280 : 800)
#define APP_SCREEN_H (USE_FULLSCREEN ? 800 : 600)

#define NIMAGE 14

//#define APP_SCREEN_W 1920
//#define APP_SCREEN_H 1080

void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    //ici : identique à celle du bureau
    set_color_depth(desktop_color_depth());
    //set_color_depth(24);
    if(set_gfx_mode(APP_CARD, APP_SCREEN_W, APP_SCREEN_H, 0, 0) != 0)
    {
        allegro_message("%s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

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
    initialisation_allegro();
    install_mouse();
    char decorPath[1024];
    // Données géométriques de l'animation
    int x,y;
    int dx,dy;
    int tx,ty;

    // Pour pouvoir avancer très lentement on avance moins souvent
    //  ( ajouter dx une fois tous les tmpdx, initialement à chaque fois )
    int cptdx=0, tmpdx=5;

    // Gestion de l'enchainement des images de la séquence
    // indice de l'image courante
    int imgcourante=0;
    // on passe à l'image suivante une fois tous les tmpimg
    int cptimg=0, tmpimg=7;

    // Séquence d'animation
    BITMAP *img[NIMAGE];

    // La tempo générale (fonction rest) sera réglable
    int tempoglobale=10;

    // Pour charger la séquence
    int i;
    char nomfichier[256];

    sprintf(decorPath, "../images/decorbis%s-24.bmp", (USE_FULLSCREEN) ? "1280x800" : "800x600");

    BITMAP *decor = load_bitmap(decorPath, NULL);
    if (!decor) {
        allegro_message("Echec chargement bitmap '%s' [%s]", decorPath, allegro_error);
        exit(EXIT_FAILURE);
    }

    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

#if 0
    BITMAP *ZeldaStatiqueTir=load_bitmap("../SpritesAnimation/LinkStatique.bmp", NULL);
    if (!ZeldaStatiqueTir) {
        allegro_message("Echec chargement bitmap '%s' [%s]", decorPath, allegro_error);
        exit(EXIT_FAILURE);
    }
#endif



    if (USE_FULLSCREEN) {
        blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    else {
        stretch_blit(decor, page,
                     0, 0, decor->w, decor->h,
                     0, 0, SCREEN_W, SCREEN_H);
    }

    // Position de départ
    //x=400;
    //y=640;

    //draw_sprite(page, ZeldaStatiqueTir, x, y);
    //masked_blit(ZeldaStatiqueTir, page, 0, 0, x, y, ZeldaStatiqueTir->w, ZeldaStatiqueTir->h);

    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // charger les images de la séquence d'animation
    for (i=0;i<NIMAGE;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"../SpritesAnimation/deplacement/Warrior%d.bmp",i);

        img[i] = load_bitmap(nomfichier,NULL);
        if (!img[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }


    // initialisation des données du personnage zelda

    tx = img[0]->h; // pour la taille on se base sur la 1ère image de la séquence
    ty = img[0]->w;
    x = 0;
    y = SCREEN_W/2-tx;
    dx = 5;
    dy = 0;

    while (!key[KEY_ESC]) {
        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // appel d'un sous programme de réglage interactif des parametres
        // ( seulement utile sur cet exemple ou pour du debug )
        reglages(page,&tempoglobale,&dx,&tmpdx,&tmpimg);

        // gestion déplacement du chat
        if ( (x<0 && dx<0) || (x+tx>SCREEN_W && dx>0) )
            dx = -dx;

        cptdx++;
        if (cptdx>=tmpdx){
            cptdx=0;
            x+=dx;
        }

        //y+=dy;

        // gestion enchainement des images
        // incrémenter imgcourante une fois sur tmpimg
        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50; // limite pour éviter blocage

        cptimg++;
        if (cptimg >= tmpimg){
            cptimg = 0;
            imgcourante = (imgcourante + 1) % NIMAGE;
            //imgcourante++;
            //cptimg = 0;
        }



#if 0
        cptimg++;
        if (cptimg>=tmpimg){
            cptimg=0;

            imgcourante++;
#endif




            // quand l'indice de l'image courante arrive à NIMAGE
            // on recommence la séquence à partir de 0
            if (imgcourante>=NIMAGE){
                imgcourante=0;
        }

        // afficher l'image courante du chat (selon le sens...)
        if (dx>=0) {
            //blit(img[imgcourante],page,0,0,x,y,img[imgcourante]->w,img[imgcourante]->h);
            draw_sprite(page,img[imgcourante],x,y);
        }
        else {
            draw_sprite_h_flip(page,img[imgcourante],x,y);
        }
        // affichage du buffer à l'écran
        textprintf_ex(page,font,10,10,makecol(255,255,255),0,
"img=%d cptimg=%d tmpimg=%d",imgcourante,cptimg,tmpimg);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(tempoglobale);
    }



    //destroy_bitmap(page);
    //destroy_bitmap(decor);
    allegro_exit();
    return 0;
}
END_OF_MAIN()