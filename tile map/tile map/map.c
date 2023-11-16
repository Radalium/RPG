#include "map.h"
#include "tools.h"
#include "player.h"
#include "musique.h"
#define TEXTURE_PATH "../Ressources/Textures/"


sfIntRect chestrect = { 0,0,32,32 };
sfVector2f chestpos = { 0.0f ,0.0f };

sfSprite* tileSprite;
sfTexture* tileTexture;
sfIntRect tileRect;
sfVector2f position = { 0.0f ,0.0f };
sfVector2i Tposition = { 0 ,0 };
int ntile = 0;
float timer_c = 0.0f;

FILE* fichier;

char map[60][200];






void initMap()
{
	// Initialisation de la map | ouverture du fichier MAP.bin et lecture du contenu dans le tableau map 
	fichier = fopen("MAP.bin", "r");
	fread(map, sizeof(char), 12000, fichier);
	fclose(fichier);


 	// Initialisation coffre 
	chesttexture = sfTexture_createFromFile(TEXTURE_PATH"coffre32.png", NULL);
	chest = sfSprite_create();
	sfSprite_setTexture(chest, chesttexture, sfTrue);
	sfSprite_setTextureRect(chest, chestrect);


	// Initialisation tileset
	tileTexture = sfTexture_createFromFile(TEXTURE_PATH"tileset.png", NULL);
	tileSprite = sfSprite_create();
	sfSprite_setTexture(tileSprite, tileTexture, sfTrue);

	
	tileRect.left = 32;
	tileRect.top = 0;
	tileRect.width = 32;
	tileRect.height = 32;
}


int coffre = 0;
float timer2 = 0.0f;
float timer = 0.0f;
int TailleBrush = 0;


void updateMap(sfRenderWindow* _window, sfView* _cam)
{
	// Initatisation des variables
	
	
	timer2 += GetDeltaTime();

	sfVector2i mousePosition;
	sfVector2i pixelPos = sfMouse_getPositionRenderWindow(_window);
	sfVector2f worldPos = sfRenderWindow_mapPixelToCoords(_window, pixelPos, cam);
	mousePosition = sfMouse_getPosition(_window);

	// A REVOIR | Gestion du changement de mode de jeu
	
	
		




	Tposition.x = (float)worldPos.x / 32;
	Tposition.y = (float)worldPos.y / 32;
	timer += GetDeltaTime();

	// Gestion de l'édition de la map
	if (iModeDeJeu == 1)
	{
		
		// Affichage du mode édition pour la map 
		if (mousePosition.x < 800 && mousePosition.y < 600 && mousePosition.x>0 && mousePosition.y>0)
		{
			// Si le bouton gauche de la souris est presser alors on change la case de la map
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				if (TailleBrush == 0)
				{
					// Gestion de la taille du pinceau 1x1
					map[Tposition.y][Tposition.x] = ntile;
				}
				if (TailleBrush == 1)
				{	// Gestion de la taille du pinceau 3x3
					map[Tposition.y + 1][Tposition.x] = ntile;
					map[Tposition.y - 1][Tposition.x] = ntile;
					map[Tposition.y][Tposition.x + 1] = ntile;
					map[Tposition.y][Tposition.x - 1] = ntile;
					map[Tposition.y + 1][Tposition.x + 1] = ntile;
					map[Tposition.y + 1][Tposition.x - 1] = ntile;
					map[Tposition.y - 1][Tposition.x + 1] = ntile;
					map[Tposition.y - 1][Tposition.x - 1] = ntile;
					map[Tposition.y][Tposition.x] = ntile;
				}
			}
		}

		// Si le bouton droit de la souris est pressée alors on change ntile 
		if (sfMouse_isButtonPressed(sfMouseRight) && timer > 0.3f)
		{
			timer = 0.0f;
			ntile++;
			if (ntile > 15)
				ntile = 0;
		}

		// Si la touche I est pressée alors on change la taille du pinceau
		if (sfKeyboard_isKeyPressed(sfKeyI) && timer > 0.3f)
		{
			timer = 0.0f;
			TailleBrush = (1 + TailleBrush) % 2;
		}

		// Si la touche M est pressée alors on sauvegarde la map
		if (sfKeyboard_isKeyPressed(sfKeyM) && timer > 0.3f)
		{

			fichier = fopen("MAP.bin", "w");
			fwrite(map, sizeof(char), 12000, fichier);
			fclose(fichier);
		}
	}

	timer_c += GetDeltaTime();

	if (iModeDeJeu == 0)
	{
		if (sfKeyboard_isKeyPressed(sfKeyO))
		{

			coffre = 1;
			
		}

		if (coffre == 1)
		{
			Openchest();
		}
		

		
	}

	
}

int blocage = 0;

void Openchest()
{
	
	if (timer_c >= 0.8f)
	{
		timer_c = 0;
		if (blocage ==0)
		{
			if (chestrect.left == 64)
			{
				blocage = 1;
			}
			chestrect.left += 32;
			sfSprite_setTextureRect(chest, chestrect);
			
		}
	}
}



void displayMap(sfRenderWindow* _window, sfView* _cam)
{
	

	sfVector2i mousePosition;
	sfVector2i pixelPos = sfMouse_getPositionRenderWindow(_window);
	sfVector2f worldPos = sfRenderWindow_mapPixelToCoords(_window, pixelPos, cam);
	mousePosition = sfMouse_getPosition(_window);
	
	/*if (iModeDeJeu == 0)
	{
		sfRenderWindow_setMouseCursorVisible(_window, sfFalse);
	}*/

	// Affichage de la map
	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			// Affichage des cases de la map en fonction de leur type
			switch (map[y][x])
			{
			case 0:
				tileRect.left = 32;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 1:
				tileRect.left = 64;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 2:
				tileRect.left = 96;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 3:
				tileRect.left = 128;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 4:
				tileRect.left = 160;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 5:
				chestpos.x = x * 32;
				chestpos.y = y * 32;
				sfSprite_setPosition(chest, chestpos);
				sfSprite_setTextureRect(chest, chestrect);
				sfRenderWindow_drawSprite(_window, chest, NULL);
				break;
			case 6:
				tileRect.left = 32 * 7;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 7:
				tileRect.left = 32 * 8;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 8:
				tileRect.left = 32 * 9;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 9:
				tileRect.left = 32 * 10;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 10:
				tileRect.left = 32 * 11;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 11:
				tileRect.left = 32 * 12;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 12:
				tileRect.left = 32 * 13;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 13:
				tileRect.left = 32 * 14;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 14:
				tileRect.left = 32 * 15;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 15:
				tileRect.left = 32 * 16;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			}
		}
	}

	// Affichage de la selection du pinceau

	if (iModeDeJeu == 1)
	{	// Si le mode de jeu est en mode édition alors on affiche la selection du pinceau
		switch (ntile)
		{
		case 0:
			tileRect.left = 32;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 1:
			tileRect.left = 32 * 2;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 2:
			tileRect.left = 32 * 3;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 3:
			tileRect.left = 32 * 4;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 4:
			tileRect.left = 32 * 5;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 5:
			tileRect.left = 32 * 6;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 6:
			tileRect.left = 32 * 7;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 7:
			tileRect.left = 32 * 8;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 8:
			tileRect.left = 32 * 9;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 9:
			tileRect.left = 32 * 10;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 10:
			tileRect.left = 32 * 11;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 11:
			tileRect.left = 32 * 12;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 12:
			tileRect.left = 32 * 13;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 13:
			tileRect.left = 32 * 14;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 14:
			tileRect.left = 32 * 15;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 15:
			tileRect.left = 32 * 16;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		}
	}





}


sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse)
{
	// Gestions des collisions avec les murs

	
	sfVector2i fpos;
	sfVector2i fpos2;
	if (iModeDeJeu == 0)
	{ // Quand le mode de jeu est en gameplay | Gestions des collisions
		switch (_direction)
		{
			// Gestions des déplacements du personnage en fonction de la direction

		case HAUT:
			// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
			fpos.y = (_sprite.top - 2 + _vitesse.y * GetDeltaTime()) / 32;
			fpos.x = (_sprite.left + _vitesse.x * GetDeltaTime()) / 32;
			fpos2.y = (_sprite.top - 2 + _vitesse.y * GetDeltaTime()) / 32;
			fpos2.x = (_sprite.width + _sprite.left + _vitesse.x * GetDeltaTime()) / 32;
			
			// Si la case est 5 4 3 9 alors, on renvoie vrai || A REVOIR
			if ((map[fpos.y][fpos.x] < 6 && map[fpos.y][fpos.x] >2) || (map[fpos2.y][fpos2.x] < 6 && map[fpos2.y][fpos2.x] >2) || (map[fpos2.y][fpos2.x] == 9 || map[fpos.y][fpos.x] == 9))
			{
				return sfTrue;
			}
			else if (map[fpos.y][fpos.x] == 2 || map[fpos2.y][fpos2.x] == 2)
			{
				// Renvoie 2 pour stipuler que la case est de l'eau
				return sfTrue + 1;
			}
			else return sfFalse;
			break;
		case BAS:
			// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
			fpos.y = (_sprite.top + _sprite.height + 2 + _vitesse.y * GetDeltaTime()) / 32;
			fpos.x = (_sprite.left + _vitesse.x * GetDeltaTime()) / 32;
			fpos2.y = (_sprite.top + _sprite.height + 2 + _vitesse.y * GetDeltaTime()) / 32;
			fpos2.x = (_sprite.left + _sprite.width + _vitesse.x * GetDeltaTime()) / 32;

			// Si la case est 5 4 3 7 alors, on renvoie vrai
			if ((map[fpos.y][fpos.x] < 6 && map[fpos.y][fpos.x] >2) || (map[fpos2.y][fpos2.x] < 6 && map[fpos2.y][fpos2.x] > 2) || (map[fpos2.y][fpos2.x] == 7 || map[fpos.y][fpos.x] == 7))
			{
				return sfTrue;
			}
			else if (map[fpos.y][fpos.x] == 2 || map[fpos2.y][fpos2.x] == 2)
			{
				// Renvoie 2 pour stipuler que la case est de l'eau
				return sfTrue + 1;
			}
			else return sfFalse;
			break;
		case DROITE:
			// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
			fpos.y = (_sprite.top + _vitesse.y * GetDeltaTime()) / 32;
			fpos.x = (_sprite.left + _sprite.width + 2 + _vitesse.x * GetDeltaTime()) / 32;
			fpos2.y = (_sprite.top + _sprite.height + _vitesse.y * GetDeltaTime()) / 32;
			fpos2.x = (_sprite.left + _sprite.width + 2 + _vitesse.x * GetDeltaTime()) / 32;

			// Si la case est 5 4 3 10 alors, on renvoie vrai
			if ((map[fpos.y][fpos.x] < 6 && map[fpos.y][fpos.x] >2) || (map[fpos2.y][fpos2.x] < 6 && map[fpos2.y][fpos2.x] > 2) || (map[fpos2.y][fpos2.x] == 10 || map[fpos.y][fpos.x] == 10))
			{
				return sfTrue;
			}
			else if (map[fpos.y][fpos.x] == 2 || map[fpos2.y][fpos2.x] == 2)
			{
				// Renvoie 2 pour stipuler que la case est de l'eau
				return sfTrue + 1;
			}
			else return sfFalse;

			break;
		case GAUCHE:
			// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
			fpos.y = (_sprite.top + _sprite.height + _vitesse.y * GetDeltaTime()) / 32;
			fpos.x = (_sprite.left - 2 + _vitesse.x * GetDeltaTime()) / 32;
			fpos2.y = (_sprite.top + _vitesse.y * GetDeltaTime()) / 32;
			fpos2.x = (_sprite.left - 2 + _vitesse.x * GetDeltaTime()) / 32;

			// Si la case est 5 4 3 8 alors, on renvoie vrai
			if ((map[fpos.y][fpos.x] < 6 && map[fpos.y][fpos.x] >2) || (map[fpos2.y][fpos2.x] < 6 && map[fpos2.y][fpos2.x] > 2) || (map[fpos2.y][fpos2.x] == 8 || map[fpos.y][fpos.x] == 8))
			{
				return sfTrue;
			}
			else if (map[fpos.y][fpos.x] == 2 || map[fpos2.y][fpos2.x] == 2)
			{
				// Renvoie 2 pour stipuler que la case est de l'eau
				return sfTrue + 1;
			}
			else return sfFalse;
			break;
		}
	
	}
	if (iModeDeJeu == 1)
	{ // Quand le mode de jeu est en mode édition de map | pas de collisions
		return sfFalse;
	}

}


