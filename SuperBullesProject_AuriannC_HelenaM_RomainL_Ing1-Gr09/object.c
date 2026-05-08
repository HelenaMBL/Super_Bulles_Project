#include <allegro.h>
#include "object.h"


void deplacement_Bulle(Objet *bulle) {
    bulle->y += 1;
    int dx=1-(rand()%2)*2;
    switch (rand()%3) {
        case 1:
            bulle->x += dx +1;
            break;

        case 2:
            bulle->x += dx -1;
            break;
    }
    bulle->y += 1;
    bulle->x += dx +1;



    /*
    int dx;
    if (bulle->x > SCREEN_W / 2) {
        int choix = rand() % 2 +1;

        if (choix == 1) {
            // diagonale gauche (retour centre)
            bulle->vx = -1;
            bulle->vy = 2;
        }
        else if (choix == 2) {
            // légère droite
            bulle->vx = 1;
            bulle->vy = 2;
        }
        else {
            bulle->vx = 0;


        }


    }
    */
}

void draw_objectSprite(Objet* p, BITMAP* page) {
    if (p->flip)
        draw_sprite_h_flip(page,p->animation->images[p->animation->currentFrame], p->x, p->y);
    else
        draw_sprite(page,p->animation->images[p->animation->currentFrame], p->x, p->y);
}
