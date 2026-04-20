#include <stdio.h>
#include <allegro.h>

#define APP_SCREEN_W 800
#define APP_SCREEN_H 600
#define USE_FULLSCREEN 1
//#define USE_FULLSCREEN 0
#define APP_CARD (USE_FULLSCREEN ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED)


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
void reglages(BITMAP *bmp,int *ptempoglobale,int *pdx,int *ptmpdx,int *ptmpimg);


// Il y a 6 images dans la séquence du chat
//  ( à terme il faudrait gérer ça en allocation dynamique )
#define NIMAGE 1


int main()
{
    initialisation_allegro();

    BITMAP *decor = load_bitmap("../images/decor-800x600-32.bmp", NULL);
    if (!decor) {
        allegro_message("Echec chargement bitmap [%s]", allegro_error);
        exit(EXIT_FAILURE);
    }


    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);
    stretch_blit(decor, page,
                 0, 0, decor->w, decor->h,
                 0, 0, SCREEN_W, SCREEN_H);

    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    int tempoglobale = 30;
    while (!key[KEY_ESC]) { rest(tempoglobale); }

    destroy_bitmap(page);
    destroy_bitmap(decor);
    allegro_exit();
    return 0;
}
END_OF_MAIN()

#if 0
int main()
{

    initialisation_allegro();

    BITMAP *decor;
    decor = load_bitmap("../images/decor.bmp", NULL);
    if (!decor)
    {
        allegro_message("%s", allegro_error);
        exit(EXIT_FAILURE);
    }

    // Créer un bitmap 32 bits de la même taille
    BITMAP *decor_32 = create_bitmap_ex(32, decor->w, decor->h);

    // Copier en convertissant la profondeur automatiquement
    blit(decor, decor_32, 0, 0, 0, 0, decor->w, decor->h);





    // Convertir le bitmap dans la profondeur de l'écran
    BITMAP *decor_conv = create_bitmap(decor_32->w, decor_32->h);
    blit(decor_32, decor_conv, 0, 0, 0, 0, decor->w, decor->h);
    // Libérer l'original
    destroy_bitmap(decor_32);
    destroy_bitmap(decor);

    // Double buffer
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    // Étirer le décor converti sur tout l'écran
    stretch_blit(decor_conv, page,
                 0, 0, decor_conv->w, decor_conv->h,
                 0, 0, SCREEN_W, SCREEN_H);

    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    int tempoglobale = 30;
    while (!key[KEY_ESC])
    {
        rest(tempoglobale);
    }

    destroy_bitmap(page);
    destroy_bitmap(decor_conv);
    allegro_exit();
    return 0;
}
END_OF_MAIN()

#endif

