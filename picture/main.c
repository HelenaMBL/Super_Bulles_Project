#include <stdio.h>
#include <allegro.h>

#define APP_SCREEN_W 1280
#define APP_SCREEN_H 1024

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



    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    /// si échec, le programme s'arrête
    //if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,1920,1080,0,0)!=0)
    //if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0) != 0)
    //{// Essayer fullscreen, sinon fenêtré
    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, APP_SCREEN_W, APP_SCREEN_H, 0, 0) != 0)
    //if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1920, 1080, 0, 0) != 0)
    {
        if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, APP_SCREEN_W, APP_SCREEN_H, 0, 0) != 0)
        {
            allegro_message("%s", allegro_error);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }



    //allegro_exit();
    //exit(EXIT_FAILURE);
}


// Sous programme pour jouer avec les parametres
void reglages(BITMAP *bmp,int *ptempoglobale,int *pdx,int *ptmpdx,int *ptmpimg);


// Il y a 6 images dans la séquence du chat
//  ( à terme il faudrait gérer ça en allocation dynamique )
#define NIMAGE 1


int main()
{
    initialisation_allegro();
    //allegro_init();
    //int x,y;

    BITMAP *decor = load_bitmap("../images/decor-1280x1024-32.bmp", NULL);
    if (!decor) {
        allegro_message("%s", allegro_error);
        allegro_message("toto");
        exit(EXIT_FAILURE);
        return 0;
    }


    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);
    //blit(decor,screen,0,0, (SCREEN_W-decor->w)/2, (SCREEN_H-decor->h)/2, decor->w, decor->h);
    //blit(decor,page,0,0, (SCREEN_W), (SCREEN_H), decor->w, decor->h);
    /*int depy=5;
    int touche;
    // Boucle interactive
    while (!key[KEY_ESC]) {
        if(keypressed()){
            touche=readkey();
            touche=touche>>8;
            if (touche==KEY_SPACE){
                x=rand()%(SCREEN_W-decor->w);
                y=rand()%(SCREEN_H-decor->h);
            }
            if (touche==KEY_UP) {
                if (y-depy>0) y-=depy;
            }
            if (touche==KEY_DOWN) {
                if (y+decor->h+depy<SCREEN_H) y+=depy;
            }
            if (touche==KEY_ENTER) {
                x=(SCREEN_W-decor->w)/2;
                y=(SCREEN_H-decor->h)/2;
            }
            clear_bitmap(screen);
            blit(decor,screen,0,0, x, y, decor->w, decor->h);
        }
    }
    //quand on a plus besoin de la bitmap, on la détruit

    allegro_exit();//x= (SCREEN_W-decor->w)/2;
    //y= (SCREEN_H-decor->h)/2;

    // Un seul bitmap converti en profondeur écran
    //BITMAP *decor_conv = create_bitmap_ex(32, decor->w, decor->h);
    //blit(decor, decor_conv, 0, 0, 0, 0, decor->w, decor->h);
    //destroy_bitmap(decor);

     */
    // Pourcentage de zoom (100 = taille normale, 50 = moitié, 200 = double)
    int zoom = 100; // changez cette valeur

    int largeur_affichee = (decor->w * zoom) / 100;
    int hauteur_affichee = (decor->h * zoom) / 100;
    stretch_blit(decor, page,
                 0, 0, largeur_affichee, hauteur_affichee,        // source : image entière
                 0, 0, SCREEN_W, SCREEN_H); // destination : zoomée

    //stretch_blit(decor_conv, page,
                // 0, 0, decor_conv->w, decor_conv->h,
                // 0, 0, SCREEN_W, SCREEN_H);
    //blit(decor_conv, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    int tempoglobale = 30;
    while (!key[KEY_ESC]) { rest(tempoglobale); }

    destroy_bitmap(page);
    destroy_bitmap(decor);
    //destroy_bitmap(decor_conv);
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

