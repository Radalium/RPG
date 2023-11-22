#pragma once
#include"SFML/Graphics.h"
#include"tools.h"
#include"player.h"


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

void initMap();
void updateMap(sfRenderWindow* _window, sfView* _cam);

sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse);

void displayMap(sfRenderWindow* _window, sfView* _cam);

void Openchest(int i);


int onestsurquelcase(sfFloatRect _sprite);
void appararitionObjet();


void ouvertureporte();



