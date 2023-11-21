#pragma once
#include"SFML/Graphics.h"
#include"tools.h"
#include"player.h"


int iModeDeJeu;

void initMap();
void updateMap(sfRenderWindow* _window, sfView* _cam);

sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse);

void displayMap(sfRenderWindow* _window, sfView* _cam);

void Openchest(int i);


void onestsurquelcase(sfFloatRect _sprite);

