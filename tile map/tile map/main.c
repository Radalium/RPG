#include "SFML/graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "tools.h"
#include <math.h>
#include <time.h>
#include "player.h"
#include "menu.h"
#include "NPC.h"
#include "musique.h"


#define TEXTURE_PATH "../Ressources/Textures/"



int main()
{
	
	float animTime = 0.0f;


	//init
	initTools();
	sfVideoMode mode = { 800, 600, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, NULL);

	actualState = MENU;

	sfEvent event;
	initMusique();
	initMap();
	initPlayer();
	initCam();
	initMenu();
   	initNPC();
	
	float timer = 0.0f;

	//boucle de jeu
	while (sfRenderWindow_isOpen(window))
	{
		//timer
		restartClock();
		timer += GetDeltaTime();

		//update
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}
		}
		if (actualState == MENU)
		{
			sfMusic_stop(editeur);
			updateMenu(window);

		}
		else if (actualState == JOUER)
		{
			sfMusic_stop(menu);
			sfMusic_stop(editeur);
			updateNPC(window);

			iModeDeJeu = 0;
			GameMod_player();

			updatePlayer(window);
			updateMap(window, cam);

		}
		else if (actualState == EDITEUR)
		{	iModeDeJeu = 1;
			sfMusic_stop(menu);
			EditorMod_player();
			updateMap(window, cam);
			updatePlayer(window);
		}

		else if (actualState == QUITTER)
			sfRenderWindow_close(window);



		//affichage
		sfRenderWindow_clear(window, sfBlack);

		if (actualState == MENU)
		{
			DisplayMenu(window);
			updateMusique();
		}
		else if (actualState == JOUER)
		{
			displayMap(window, cam);
			displayCam(window);
			displayPlayer(window);
			DisplayNPC(window);
		}
		else if (actualState == EDITEUR)
		{
			displayMap(window, cam);
			displayCam(window);
		}

		
		sfRenderWindow_display(window);

	}
	return 0;
}


