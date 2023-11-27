#include "cam.h"
#include "tools.h"
#include "SFML/Graphics.h"
#include "map.h"
#include "player.h"

int Editor = 0;

sfVector2f camrect = { 200.f , 150.f };

void initCam()
{
	// Initialisation de la view
	cam = sfView_create();
	sfView_setSize(cam ,camrect);
}

sfVector2f sicam = { 2000.f ,1500.f };
float timer;
void updateCam(sfVector2f _playerpos)
{
	if (Editor == 1)
	{
		sfView_setCenter(cam, _playerpos);
		timer += GetDeltaTime();
		if (sfKeyboard_isKeyPressed(sfKeyUp) && timer > 0.1f)
		{
			timer = 0.0f;
			sicam.y = sicam.y * 0.9f;
			sicam.x = sicam.x * 0.9f;
		}
		if (sfKeyboard_isKeyPressed(sfKeyDown) && timer > 0.1f)
		{
			timer = 0.0f;
			sicam.y = sicam.y * 1.1f;
			sicam.x = sicam.x * 1.1f;
		}
		camrect.x = sicam.x;
		camrect.y = sicam.y;
		sfView_setSize(cam, camrect);
	}


	// Update de la view


	if (Editor == 0)
	{
		if (_playerpos.y < 75)
		{
			camrect.y = 75;
		}

		else if (_playerpos.y > 1845)
		{
			camrect.y = 1845;
		}

		else {
			camrect.y = _playerpos.y;
		}

		if (_playerpos.x < 100)
		{
			camrect.x = 100;
		}

		else if (_playerpos.x > 6300)
		{
			camrect.x = 6300;

		}
		else {
			camrect.x = _playerpos.x;
		}

		sfView_setCenter(cam, camrect);
		
	}
}
void displayCam(sfRenderWindow* _window)
{ 
	// Affichage de la view
	sfRenderWindow_setView(_window, cam); 
	
}

void EditorMod_cam()
{
	Editor = 1;

	// Passage en mode édition de map

}

void GameMod_cam()
{
	// Passage en mode jeu 
	Editor = 0;
	camrect.x = 200.f;
	camrect.y = 150.f;
	sfView_setSize(cam, camrect);
}
