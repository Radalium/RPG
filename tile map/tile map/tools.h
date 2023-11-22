#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"cam.h"
#include "SFML/Audio.h"




// Enum pour les statues du jeu
typedef enum state
{
	MENU = 0,
	JOUER,
	EDITEUR,
	QUITTER,
	TOUCHES
} state;

state actualState;


void initTools();
void restartClock();
float GetDeltaTime();

sfVector2f vector2f(float _x, float _y);
