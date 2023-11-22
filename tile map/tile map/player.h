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

sfVector2f Pposition;
sfVector2f actualposJ;
void updatePlayer();
int blocage3;

void displayPlayer(sfRenderWindow* _window);
void EditorMod_player();
void GameMod_player();
void Vplus();
void Vmoins();

sfBool CalculD(sfVector2f _obj, float _rayon2);

sfBool CalculD(sfVector2f _obj, float _rayon2);
void couv(int _chestouvert);

void animpcoffre(int _i);


