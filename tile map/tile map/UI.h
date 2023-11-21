#pragma once
#include "SFML/Graphics.h"

int nmcle;

void initUI();

void updateUI(sfVector2f _playerpos);

void displayUI(sfRenderWindow* _window, sfView* _cam);

