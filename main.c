#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "animation.h"

#define USE_FULLSCREEN 0
#define APP_SCREEN_W 1280
#define APP_SCREEN_H 800
#define APP_CARD (USE_FULLSCREEN ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED)
#define NIMAGE 14
#define IMAGESTAT 7
#define FRAME_DURATION 80
#define DELTA_X 14
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define ORANGE "\033[34m"


typedef struct{
int x;
int y;
int dx,dy;
int tx,ty;
}Joueur;			//joueur

typedef struct{
int x;
const int y;
}boss;


typedef struct{
    char pseudo[40];
    int vie;
    float temps;
    int niveau;
    int score;
}Partie	;		//partie

typedef struct{
int x;
int y;
int tx;
int ty;
}Bulle	;		//bulle




void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    //ici : identique à celle du bureau
    set_color_depth(desktop_color_depth());
    //set_color_depth(24);
    if(set_gfx_mode(APP_CARD, 1280, 800, 0, 0) != 0)
    {
        allegro_message("%s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

clock_t diffMilliseconds(clock_t end, clock_t start) {
    return (end - start) * 1000 / CLOCKS_PER_SEC;
}
void lire(Partie* p, Joueur *j) {
    char nomfichier[60];
    snprintf(nomfichier, sizeof(nomfichier), "sauvegarde/%s.txt", p->pseudo);

    FILE* pf = fopen(nomfichier, "r");
    if (!pf) {
        printf(YELLOW"Fichier inexistant -> création de %s\n" RESET,nomfichier);
        return;
    }

    int ok = fscanf(pf,
        "%39[^;];%d;%f;%d;%d;%d;%d;%d;%d;%d;%d",
        p->pseudo,
        &p->vie,
        &p->temps,
        &p->niveau,
        &j->x,
        &j->y,
        &j->dx,
        &j->dy,
        &j->tx,
        &j->ty,
        &p->score
    );

    if (ok != 11) {
        perror(RED "Fichier corrompu: %s\n"RESET);
    }
    perror(nomfichier);
    printf(GREEN"%s a ete lu avec succes !\n"RESET, nomfichier);


    fclose(pf);
}




void enregistrer(Partie* p, Joueur *j) {
    char nomfichier[60];
    FILE* pf;
    snprintf(nomfichier, sizeof(nomfichier), "sauvegarde/%s.txt", p->pseudo);
    pf = fopen(nomfichier, "w");

    if (!pf) {
        perror("fopen a échoué");
        printf("Nom fichier = [%s]\n", nomfichier);
        fclose(pf);
        return;
    }



    if (fprintf(pf, "%s;%d;%f;%d;%d;%d;%d;%d;%d;%d;%d", p->pseudo, p->vie, p->temps,p->niveau,j->x,j->y,j->dx,j->dy,j->tx,j->ty,p->score) < 0) {
        perror(RED"Erreur écriture fichier"RESET);
        fclose(pf);
        return ;
    }
    printf(GREEN"enregistrement de %s termine !", nomfichier);
    fclose(pf);
}

void affichagedata(BITMAP *bmp,Partie* p){

    textprintf_ex(bmp,font,16,20,makecol(255,255,255),0,"Niveau : %d", p->niveau);
    textprintf_ex(bmp,font,16,30,makecol(255,255,255),0,"Vie : %d",p->vie);
    textprintf_ex(bmp,font,16,40,makecol(255,255,255),0,"Temps : %f",p->temps);
    textprintf_ex(bmp,font,16,50,makecol(255,255,255),0,"score : %d",p->score);

}

void jouer(Partie* p, Joueur *j){
clock_t start= clock();
int alive=1;

int i;
Bulle bulle[9];
int tmpdx=14;
int imgcourante=0;
int cptimg=0, tmpimg=7;
BITMAP* animMarche[NIMAGE];
BITMAP* animStat[IMAGESTAT];
int tempoglobale=10;
    char decorPath[1024];

    lire(p,j);
    float temps= p->temps;
    if (temps<=0){temps=120;p->score=0;}
    if (p->vie==0){p->vie=3;p->niveau=1;temps=120;p->score=0;}
//fond

 sprintf(decorPath, "../images/decorbis1280x800-24.bmp");

BITMAP *decor = load_bitmap(decorPath, NULL);
    if (!decor) {
        allegro_message("Echec chargement bitmap '%s' [%s]", decorPath, allegro_error);
        exit(EXIT_FAILURE);
    }

BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

 blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

//perso

load_Anim(NIMAGE,"../SpritesAnimation/deplacement/Warrior%d.bmp", animMarche);
    load_Anim(IMAGESTAT,"../SpritesAnimation/WarriorStatique/WarriorStat%d.bmp", animStat);

 j->tx = animMarche[0]->w; // pour la taille on se base sur la 1ère image de la séquence
 j->ty = animMarche[0]->h;
 j->x = 0;
 j->y = SCREEN_W/2-(j->ty);
    //p->dx = 10;
    j->dy = 0;

 clock_t  lastClock = 0;
    clock_t  currentClock;




if(p->niveau <3) {
    do{
        if (key[KEY_ESC]) {
            enregistrer(p,j);
            return;
        }

        currentClock = clock();

        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);


        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50;


        if (key [KEY_RIGHT]) {
            j->dx = DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x+j->tx>SCREEN_W)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        }

        if (key[KEY_LEFT]) {
            j->dx = -DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x<=0)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        } else if (!key[KEY_RIGHT] && !key[KEY_LEFT]) {
            j->dx=0;
            if (diffMilliseconds(currentClock, lastClock) >=300) {
                lastClock = currentClock;
                imgcourante = (imgcourante + 1) % IMAGESTAT;
            }
        }
        if (j->dx>0) {
            draw_sprite(page,animMarche[imgcourante],j->x,j->y);
        }
        else if (j->dx<0) {
            draw_sprite_h_flip(page,animMarche[imgcourante],j->x,j->y);
        }
        else if (j->dx==0) {
            draw_sprite(page,animStat[imgcourante],j->x,j->y);
        }

        affichagedata(page,p);


        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


        p->temps= temps - diffMilliseconds(clock(), start) / 1000.0;
        // afficher: niveau vie temps

        /*for( i=0;i<p->niveau*3;i++){

        bulle[i]= gravite(bulle[i]);
        afficherbulle(bulle[i]);

        }
        if(degat()){
        j->vie=-;
        }*/
        //



    }while(p->vie>0 && p->temps>0);
}




if (p->niveau=3) {
    float xboss =SCREEN_W/2;
    int yboss =50;
    float deplacementboss=1;
    int degat=20;
    i=0;
    do{
        if (key[KEY_ESC]) {
            enregistrer(p,j);
            return;
        }


        currentClock = clock();

        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);


        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50;


        if (key [KEY_RIGHT]) {
            j->dx = DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x+j->tx>SCREEN_W)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        }

        if (key[KEY_LEFT]) {
            j->dx = -DELTA_X;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x<=0)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        } else if (!key[KEY_RIGHT] && !key[KEY_LEFT]) {
            j->dx=0;
            if (diffMilliseconds(currentClock, lastClock) >=300) {
                lastClock = currentClock;
                imgcourante = (imgcourante + 1) % IMAGESTAT;
            }
        }
        if (j->dx>0) {
            draw_sprite(page,animMarche[imgcourante],j->x,j->y);
        }
        else if (j->dx<0) {
            draw_sprite_h_flip(page,animMarche[imgcourante],j->x,j->y);
        }
        else if (j->dx==0) {
            draw_sprite(page,animStat[imgcourante],j->x,j->y);
        }

        affichagedata(page,p);

        xboss =xboss + deplacementboss/2;
        if (xboss>SCREEN_W-40) deplacementboss =-2;
        if (xboss<40) deplacementboss =+2;
        circlefill(page,(int)xboss,yboss ,40,makecol(153,153,153));
        rectfill(page,
                 (int)xboss-40, 5,
                 (int)xboss+40, 10,
                 makecol(0,200,0));
        rectfill(page,
                (int)xboss+40 -degat, 5,
                (int)xboss+40, 10,
                makecol(200,0,0));

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);



        p->temps= temps - diffMilliseconds(clock(), start) / 1000.0;
        // afficher: niveau vie temps

        /*for( i=0;i<p->niveau*3;i++){

        bulle[i]= gravite(bulle[i]);
        afficherbulle(bulle[i]);

        }
        if(degat()){
        j->vie=-;
        }*/
        //

    }while(p->vie>0 && p->temps>0 && degat<80);
}


if (p->score<1000) {
    enregistrer(p,j);
    destroy_bitmap(decor);
    clear_bitmap(page);

    // bouton cyan
    rectfill(page,
             0, 0,
             SCREEN_W, SCREEN_H/2,
             makecol(255,0,0));

    // texte
    textout_ex(page, font,"Vous avez perdu",SCREEN_W/2, SCREEN_H/2,makecol(255,255,255),-1);

    // pseudo
    textout_ex(page, font,
               p->pseudo,SCREEN_W/2, SCREEN_H/2 +20,makecol(255,255,255),-1);

    // affichage final
    blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

}else {
    destroy_bitmap(decor);
}
    rest(5000);
}
















void Parties(Partie* partie, Joueur* joueur){


            partie->temps=120;
            partie->vie=3;
            partie->niveau=1;
    partie->score=0;
            jouer(partie,joueur); // nouvelle partie
    }



int main(){
initialisation_allegro();
int i=0;
int fin=1;
    int erreur=0;
Partie partie ={0};
Joueur joueur={0};
    int saisie_pseudo = 0;
    partie.pseudo[0] = '\0';
int choix;

    show_mouse(screen);
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *play = load_bitmap("../images/play_button_blue_24bit.bmp", NULL);

    if (!play) {
        allegro_message("Echec chargement bitmap '%s' [%s]", "../play_button_blue_24bit.bmp", allegro_error);
        exit(EXIT_FAILURE);
    }



    while (fin == 1) {
        // 1. saisie clavier (TOUJOURS)


            if (keypressed()) {
                int k = readkey();
                char c = k & 0xFF;
                int code = k >> 8;

                // ENTER = toggle saisie
                if (code == KEY_ENTER) {
                    saisie_pseudo = !saisie_pseudo;
                }
                if (key[KEY_ESC]) {
                    fin = 0;
                }
                if (saisie_pseudo) {
                     if (saisie_pseudo && c == '\b' && i > 0) {
                        i--;
                        partie.pseudo[i] = '\0';
                    }
                    // caractères normaux
                     if (saisie_pseudo && i < 39 && c >= 32) {
                        partie.pseudo[i++] = c;
                        partie.pseudo[i] = '\0';
                    }
                }

                // flush buffer
                while (keypressed())
                    readkey();
            }


        // 2. clic souris (validation)
        if (mouse_b & 1 ) {

            int couleur = getpixel(screen, mouse_x, mouse_y);
            if (couleur == makecol(153, 153, 153))saisie_pseudo = !saisie_pseudo;

            if (couleur == makecol(0, 0, 255) && saisie_pseudo==0 && partie.pseudo[0] != '\0') {
                choix = 1;
            }
            if (couleur == makecol(0, 0, 255) && partie.pseudo[0] == '\0')erreur=1;
            while(mouse_b & 1);
        }

        // 3. affichage
        clear_bitmap(page);

        // image du bouton
        stretch_sprite(page, play, SCREEN_W/2 -100, SCREEN_H/2 -100, 200, 200);

        // bouton cyan
        rectfill(page,
                 SCREEN_W/3 -30, SCREEN_H/4 -40,
                 2*SCREEN_W/3 +30, SCREEN_H/4 +40,
                 makecol(153,153,153));
        circlefill(page,SCREEN_W/3 -30,SCREEN_H/4 ,40,makecol(153,153,153));
        circlefill(page,2*SCREEN_W/3 +30,SCREEN_H/4 ,40,makecol(153,153,153));
        if (saisie_pseudo==1) {
            rectfill(page,
                 SCREEN_W/3 -20, SCREEN_H/4 -30,
                 2*SCREEN_W/3 +20, SCREEN_H/4 +30,
                 makecol(171,171,171));
            circlefill(page,SCREEN_W/3 -20,SCREEN_H/4 ,30,makecol(171,171,171));
            circlefill(page,2*SCREEN_W/3 +20,SCREEN_H/4 ,30,makecol(171,171,171));
        }

        // pseudo
        textout_ex(page, font,
                   partie.pseudo,
                   SCREEN_W/3 -30,  SCREEN_H/4  ,
                   makecol(255,255,255),
                   -1);
        if (erreur)textout_ex(page, font,"rentrer un pseudo",SCREEN_W/2 -68,SCREEN_H-50,makecol(255,0,0),-1);

        // affichage final
        blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);




        switch(choix){
            case 1:
                Parties(&partie,&joueur);
                choix=0;
                break;
            case 2:
                fin=0;
                destroy_bitmap(page);
                allegro_exit();



        }
    }

    return 0;

}END_OF_MAIN()
