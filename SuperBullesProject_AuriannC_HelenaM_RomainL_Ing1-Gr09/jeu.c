//
// Created by helen on 10/05/2026.
//

#include "jeu.h"
#include <stdio.h>
#include "constantes.h"
#include "object.h"
#include "allegro.h"

#if 0
void jouer(Partie* p, Objet*j){
    Bulle bulles[MAX_BULLES];
    int i;
    int gagne=0;
    for(i = 0; i < MAX_BULLES; i++)
        bulles[i].active = 0;
clock_t start= clock();
int alive=1;
    clock_t dernierTir = 0;
Bulle bulle[9];
int tmpdx=14;
int imgcourante=0;
int cptimg=0, tmpimg=7;
BITMAP* animMarche[NIMAGE];
BITMAP* animStat[IMAGESTAT];
    Projectile tirs[MAX_PROJECTILES];
int tempoglobale=10;
    char decorPath[1024];
    Bonus bonus_map[MAX_BONUS];
    int   timer_bonus_tir  = 0;   // >0 = actif
    int   timer_bonus_move = 0;

    for(i = 0; i < MAX_BONUS; i++){
        bonus_map[i].actif = 0;
    }

    // Délai de cooldown pour ne pas spammer les bonus
    int cooldown_bonus = 0;


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

    char path[256];

    for(int k=0; k<NIMAGE; k++){
        sprintf(path,
                "../SpritesAnimation/deplacement/Warrior%d.bmp",
                k);

        animMarche[k] = load_bitmap(path,NULL);
    }

    for(int k=0; k<IMAGESTAT; k++){
        sprintf(path,
                "../SpritesAnimation/WarriorStatique/WarriorStat%d.bmp",
                k);

        animStat[k] = load_bitmap(path,NULL);
    }
    int degat=0;
 j->tx = animMarche[0]->w; // pour la taille on se base sur la 1ère image de la séquence
 j->ty = animMarche[0]->h;
 j->x = 0;
    j->y = SCREEN_H - j->ty - 10;
    //p->dx = 10;
    j->dy = 0;

 clock_t  lastClock = 0;
    clock_t  currentClock;
    for(i = 0; i < MAX_PROJECTILES; i++){
        tirs[i].actif = 0;
        tirs[i].w = 8;
        tirs[i].h = 20;
    }




if(p->niveau <3) {

    for(i = 0; i < 5; i++){
        init_bulle(&bulles[i],
                   rand()%SCREEN_W,
                   100,
                   0);
    }
    do{
        int cooldown_tir = (timer_bonus_tir > 0) ? 80 : 200;
        int delta_actif = (timer_bonus_move > 0) ? (int)(DELTA_X * 1.8) : DELTA_X;
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
        for(i = 0; i < MAX_BULLES; i++){
            update_bulle(&bulles[i]);
        }
        for(i = 0; i < MAX_BULLES; i++){
            draw_bulle(page, &bulles[i]);
        }
        for(i = 0; i < MAX_BULLES; i++){
            if(!bulles[i].active) continue;

            float dx = bulles[i].x - j->x;
            float dy = bulles[i].y - j->y;

            if(dx*dx + dy*dy < (bulles[i].rayon * bulles[i].rayon)){
                p->vie--;
                bulles[i].active = 0;
            }
        }
        int nb_actives = 0;
        for(i = 0; i < MAX_BULLES; i++)
            if(bulles[i].active) nb_actives++;

        if(nb_actives == 0){
            gagne = 1;
            break;  // sort du do{}while
        }
        for(i = 0; i < MAX_PROJECTILES; i++)
        {
            if(!tirs[i].actif) continue;

            for(int b = 0; b < MAX_BULLES; b++)
            {
                if(!bulles[b].active) continue;

                if(tirs[i].x < bulles[b].x + bulles[b].rayon &&
                   tirs[i].x + tirs[i].w > bulles[b].x - bulles[b].rayon &&
                   tirs[i].y < bulles[b].y + bulles[b].rayon &&
                   tirs[i].y + tirs[i].h > bulles[b].y - bulles[b].rayon)
                {
                    tirs[i].actif = 0;
                    p->score += (bulles[b].niveau == 0) ? 100 :
            (bulles[b].niveau == 1) ? 200 : 300;
                    split_bulle(&bulles[b], bulles, bonus_map, &cooldown_bonus);

                    break;
                }
            }
        }
        if(cooldown_bonus > 0) cooldown_bonus--;

        for(i = 0; i < MAX_BONUS; i++){
            if(!bonus_map[i].actif) continue;

            // chute lente
            bonus_map[i].y += bonus_map[i].vy;

            // disparaît au sol
            if(bonus_map[i].y > SCREEN_H - 10){
                bonus_map[i].actif = 0;
                continue;
            }

            // collision joueur (AABB simple)
            if(bonus_map[i].x > j->x &&
               bonus_map[i].x < j->x + j->tx &&
               bonus_map[i].y > j->y &&
               bonus_map[i].y < j->y + j->ty)
            {
                if(bonus_map[i].type == BONUS_TIR_RAPIDE)
                    timer_bonus_tir  = DUREE_BONUS;
                else
                    timer_bonus_move = DUREE_BONUS;

                bonus_map[i].actif = 0;
            }

            draw_bonus(page, &bonus_map[i]);
        }

        // ── Décompte des timers bonus ──────────────────────────────────
        if(timer_bonus_tir  > 0) timer_bonus_tir--;
        if(timer_bonus_move > 0) timer_bonus_move--;

        if (key[KEY_ESC]) {
            enregistrer(p,j);
            return;
        }

        currentClock = clock();

        // effacer buffer en appliquant décor  (pas de clear_bitmap)



        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50;

        if(key[KEY_SPACE]){
            if(diffMilliseconds(clock(), dernierTir) > cooldown_tir){

                for(i = 0; i < MAX_PROJECTILES; i++){
                    if(tirs[i].actif == 0){

                        tirs[i].actif = 1;

                        tirs[i].x = j->x + j->tx/2;
                        tirs[i].y = j->y;

                        tirs[i].w = 11;
                        tirs[i].h = 28;

                        break;
                    }
                }

                dernierTir = clock();
            }
        }
        for(i = 0; i < MAX_PROJECTILES; i++){
            if(tirs[i].actif){
                tirs[i].y -= VITESSE_TIR;

                rectfill(page,
                         tirs[i].x,
                         tirs[i].y,
                         tirs[i].x + tirs[i].w,
                         tirs[i].y + tirs[i].h,
                         makecol(101,67,33));

                if(tirs[i].y < 0)
                    tirs[i].actif = 0;
            }
        }
        if(key[KEY_SPACE]){
            textout_ex(screen,font,"SPACE OK",10,10,makecol(255,0,0),-1);
        }
        if (key [KEY_RIGHT]) {
            j->dx = delta_actif;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x+j->tx>SCREEN_W)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        }


        if (key[KEY_LEFT]) {
            j->dx = -delta_actif;
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

        affichagedata(page, p, timer_bonus_tir, timer_bonus_move);


        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


        p->temps= temps - diffMilliseconds(clock(), start) / 1000.0;


        rest(16);
    }while(p->vie > 0 && p->temps > 0 && !gagne);
}




if (p->niveau==3) {
    float xboss =SCREEN_W/2;
    int yboss =50;
    float deplacementboss=1;

    i=0;
    do{
        int cooldown_tir = (timer_bonus_tir > 0) ? 80 : 200;
        int delta_actif  = (timer_bonus_move > 0) ? (int)(DELTA_X * 1.8) : DELTA_X;
        if (key[KEY_ESC]) {
            enregistrer(p,j);
            return;
        }


        currentClock = clock();

        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);


        if (tmpimg < 1) tmpimg = 1;
        if (tmpimg > 50) tmpimg = 50;
        if(key[KEY_SPACE] && diffMilliseconds(clock(), dernierTir) > 150){

            for(i = 0; i < MAX_PROJECTILES; i++){

                if(tirs[i].actif == 0){

                    tirs[i].actif = 1;

                    tirs[i].x = j->x + j->tx/2 - 4;
                    tirs[i].y = j->y;

                    break;
                }
            }
            dernierTir = clock();
        }

        if (key [KEY_RIGHT]) {
            j->dx = delta_actif;
            if (diffMilliseconds(currentClock, lastClock) >=FRAME_DURATION){
                if (j->x+j->tx>SCREEN_W)
                    j->dx = 0;
                j->x+=j->dx;
                imgcourante = (imgcourante + 1) % NIMAGE;
                lastClock = currentClock;
            }
        }


        if (key[KEY_LEFT]) {
            j->dx = -delta_actif;
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

        affichagedata(page, p, timer_bonus_tir, timer_bonus_move);

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
        for(i = 0; i < MAX_PROJECTILES; i++){

                    if(tirs[i].actif){

                        tirs[i].y -= VITESSE_TIR;
                        int centreBossX = (int)xboss;
                        int centreBossY = yboss;
                        int rayonBoss = 40;

                        // centre projectile
                        int projX = tirs[i].x + tirs[i].w/2;
                        int projY = tirs[i].y;

                        // distance carré
                        int dx = projX - centreBossX;
                        int dy = projY - centreBossY;

                        if(dx*dx + dy*dy <= rayonBoss*rayonBoss){

                            degat += 20;

                            tirs[i].actif = 0;

                            // limite max
                            if(degat > 80)
                                degat = 80;
                        }

                        // dessiner rectangle marron
                        rectfill(page,
                                 tirs[i].x,
                                 tirs[i].y,
                                 tirs[i].x + tirs[i].w,
                                 tirs[i].y + tirs[i].h,
                                 makecol(101,67,33));

                        // sortir écran
                        if(tirs[i].y < 0){
                            tirs[i].actif = 0;
                        }
                    }
                }

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
//printf("%d",degat);
    if(p->niveau < 3 && gagne){
        p->niveau++;
        enregistrer(p, j);

        clear_bitmap(page);
        textprintf_ex(page, font,
                      SCREEN_W/2 - 80, SCREEN_H/2 - 10,
                      makecol(0, 255, 0), -1,
                      "Niveau %d termine ! Score : %d", p->niveau - 1, p->score);

        blit(page, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        rest(3000);

        // Relancer jouer() pour le niveau suivant
        //jouer(p, j);
        return;
    }

    // ── Victoire niveau 3 (boss) ──────────────────────────────────
    if(p->niveau == 3 && degat >= 80){
        p->niveau = 1;       // retour au début pour une nouvelle partie
        p->score += 1000;    // bonus boss
        p->vie = 0;          // reset propre
        p->temps = 0;


        clear_bitmap(page);
        textprintf_ex(page, font,
                      SCREEN_W/2 - 80, SCREEN_H/2 - 10,
                      makecol(255, 215, 0), -1,
                      "BOSS VAINCU ! Score final : %d", p->score);
        blit(page, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        rest(5000);
        p->score = 0;
        enregistrer(p, j);
        return;
    }

    // ── Défaite (vies épuisées ou temps écoulé) ───────────────────
    p->vie  = 0;
    p->temps = 0;
    p->score = 0;
    enregistrer(p, j);

    clear_bitmap(page);
    textout_ex(page, font, "Vous avez perdu",
               SCREEN_W/2 - 60, SCREEN_H/2,
               makecol(255, 0, 0), -1);
    textout_ex(page, font, p->pseudo,
               SCREEN_W/2 - 20, SCREEN_H/2 + 20,
               makecol(255, 255, 255), -1);
    blit(page, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
    rest(3000);

}

#endif
