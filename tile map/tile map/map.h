#pragma once
#include"SFML/Graphics.h"
#include"tools.h"
#include"player.h"
#include "UI.h"
#include "NPC.h"


sfSprite* orberouge;
sfSprite* orbebleu;
sfSprite* orbeverte;
sfSprite* porteanim;
sfSprite* portedefin;

sfTexture* textureorberouge;
sfTexture* textureorbebleu;
sfTexture* textureorbeverte;
sfTexture* textureporteanim;
sfTexture* textureportedefin;


int iModeDeJeu;
float timer;

void initMap();
void updateMap(sfRenderWindow* _window, sfView* _cam);

sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse);

void displayMap(sfRenderWindow* _window, sfView* _cam);

//char map;

int combien_de_coffre();
int combien_de_PNJ();
int combien_de_joueur();

void Position_joueur();
void Position_NPC();

int onestsurquelcase(sfFloatRect _sprite);
void appararitionObjet();
void changementMap(int _nb, int _tmp);

void ouvertureporte();



