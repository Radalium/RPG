#pragma once
#include <SFML/Graphics/Types.h>
#include"tools.h"
#include"player.h"

int Editor;

void initCam();

void updateCam(_playerpos);

sfView* cam;
sfVector2f camrect;


void displayCam(sfRenderWindow* _window);
void EditorMod_cam();
void GameMod_cam();