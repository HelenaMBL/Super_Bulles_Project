#include <allegro.h>
#include "object.h"
#include "math.h"


void init_bulle_big(Objet* bulle, Animation* anim, int x, int y)
{
    bulle->x = x;
    bulle->y = y;
    bulle->vx = 3;
    bulle->vy = -6;
    bulle->radius = 48;
    bulle->active = true;
    bulle->flip = false;
    bulle->type = BULLE_BIG;
    bulle->animation = anim;
}

void split_bulle(Objet* big, Objet* small, Animation* smallAnim)
{
    big->active = false;

    small->x = big->x;
    small->y = big->y;
    small->vx = -big->vx;
    small->vy = -10;
    small->radius = 24;

    small->active = true;
    small->flip = false;
    small->type = BULLE_SMALL;
    small->animation = smallAnim;
}


void deplacement_Bulle(Objet *bulle) {
    if(!bulle->active)
        return;

    // Descente
    bulle->y += bulle->vy+1;

    // Rebond bas : réinitialise en haut avec une position x aléatoire
    if (bulle->y >= SCREEN_H - 100)
    {
        bulle->y = 0;
        bulle->x = rand() % (SCREEN_W - 100);
    }

    // Déplacement horizontal aléatoire
    bulle->x += bulle->vx;

    // Rebond gauche/droite : inverse vx et ajoute un peu d'aléatoire
    if (bulle->x <= 0 || bulle->x >= SCREEN_W - 100) {
        //bulle->vx = -(bulle->vx) + (rand() % 3 - 1); // -1, 0 ou +1
        bulle->vx = -(bulle->vx);
        // S'assurer que vx n'est pas nul
        if (bulle->vx == 0) {
            bulle->vx = 1;
        }
    }
}



void draw_objectSprite(Objet* p, BITMAP* page) {
    int x = p->x + p->animation->offsetX;
    int y = p->y + p->animation->offsetY;
    BITMAP* currentFrame = p->animation->images[p->animation->currentFrame];
    if (p->flip)
        draw_sprite_h_flip(page, currentFrame, x, y);
    else
        draw_sprite(page,currentFrame, x, y);
}

int collision_bulle_tir(Objet* bulle, int tirX, int tirY)
{
    if(!bulle->active)
        return 0;

    int centreX = bulle->x + 50;
    int centreY = bulle->y + 50;

    int dx = tirX - centreX;
    int dy = tirY - centreY;

    int distance = (int)sqrt(dx*dx + dy*dy);

    return distance < bulle->radius;
}
