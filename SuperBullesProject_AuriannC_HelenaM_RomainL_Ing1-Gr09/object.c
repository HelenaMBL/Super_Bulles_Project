#include <stdio.h>
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
    bulle->hidden = false;
    bulle->flip = false;
    bulle->type = BULLE_BIG;
    bulle->animation = anim;
}

void split_bulle(Objet* big, Objet* small, Animation* smallAnim)
{
    small->x = big->x;
    small->y = big->y;
    small->vx = -big->vx;
    small->vy = -10;
    small->radius = 24;

    small->hidden = true;
    small->flip = false;
    small->type = BULLE_SMALL;
    small->animation = smallAnim;
}

void deplacement_Bulle(Objet *p) {
    // Descente
    p->y += p->vy;

    if (p->y >= SCREEN_H)
    {
        p->y = SCREEN_H-100;
        p->vy = -p->vy;
    }

    if (p->y <= 0)
    {
        p->y = 0;
        p->vy = -p->vy;
    }


    // Déplacement horizontal aléatoire
    p->x += p->vx;

    // Rebond gauche/droite : inverse vx et ajoute un peu d'aléatoire
    if (p->x <= 0 || p->x >= SCREEN_W - 100) {
        //p->vx = -(p->vx) + (rand() % 3 - 1); // -1, 0 ou +1
        p->vx = -(p->vx);
        // S'assurer que vx n'est pas nul
        if (p->vx == 0) {
            p->vx = 1;
        }
    }
}

void deplacement_Objet(Objet *p) {
    if(p->hidden)
        return;

    if (strcmp(p->name, "warrior") == 0)
        return;


    int bulleNum = 0;
    if (sscanf(p->name, "bulle%d", &bulleNum) == 1)
    {
        deplacement_Bulle(p);
        return;
    }
    if (strcmp(p->name, "fleche") == 0)
    {
        if (p->y == 0) {
            p->hidden = true;
            return;
        }
        p->y -= 1;

    }
}



void draw_objectSprite(Objet* p, BITMAP* page) {

    if(p->hidden)
        return;
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
    if(!bulle->hidden)
        return 0;

    int centreX = bulle->x + 50;
    int centreY = bulle->y + 50;

    int dx = tirX - centreX;
    int dy = tirY - centreY;

    int distance = (int)sqrt(dx*dx + dy*dy);

    return distance < bulle->radius;
}
