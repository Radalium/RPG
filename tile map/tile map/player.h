#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
void initPlayer();

typedef enum  Direction Direction;
enum  Direction
{
	BAS,
	DROITE,
	GAUCHE,
	HAUT,
	IDLE
};
Direction direction;

void updatePlayer(sfRenderWindow* _window);

void displayPlayer(sfRenderWindow* _window);
void godlink2();
void nogodlink2();