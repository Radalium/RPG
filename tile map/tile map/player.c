#include "player.h"
#define TEXTURE_PATH "../Ressources/Textures/"
#include"tools.h"
#include"map.h"

sfSprite* player;
sfTexture* playertexture;
sfIntRect irect = { 0, 0, 17, 23 };
sfVector2f scale = { 0.8f,0.8f };
float animTime = 0.0f;
int frameX = 0;
int frameY = 0;
sfBool isMoving = sfFalse;
sfVector2f Pposition = { 340.0f, 340.0f };
sfVector2f vitesse = { 200.0f, 200.0f };

void initPlayer()
{
	// Initialisation du joueur

	playertexture = sfTexture_createFromFile(TEXTURE_PATH"player.png", NULL);
	player = sfSprite_create();
	sfSprite_setTexture(player, playertexture, sfTrue);
	sfSprite_setScale(player, scale);
	sfSprite_setTextureRect(player, irect);
}

void updatePlayer(sfRenderWindow* _window)
{
	// Update du joueur
	sfFloatRect playerfrect = sfSprite_getGlobalBounds(player);

	isMoving = sfFalse;
	if (sfKeyboard_isKeyPressed(sfKeyZ) && Pposition.y >0 && Pposition.y >32)
	{	// Mouvement vers le haut
		frameY = HAUT;
		if(!collision(playerfrect, HAUT , vitesse ))
		{
			Pposition.y -= vitesse.y * GetDeltaTime();
		}
		else if (collision(playerfrect, HAUT, vitesse) == 2)
		{
			Pposition.y -= (vitesse.y - 100) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyS) && Pposition.y > 0)
	{	// Mouvement vers le bas

		frameY = BAS;
		if (!collision(playerfrect, BAS, vitesse))
		{
			Pposition.y += vitesse.y * GetDeltaTime();
		}
		else if (collision(playerfrect, BAS, vitesse) == 2)
		{
			Pposition.y += (vitesse.y-100) * GetDeltaTime();
		}
		
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyQ) && Pposition.y > 0)
	{	// Mouvement vers la gauche

		frameY = GAUCHE;
		if (!collision(playerfrect, GAUCHE, vitesse))
		{
			Pposition.x -= vitesse.x * GetDeltaTime();
		}
		else if (collision(playerfrect, GAUCHE, vitesse) == 2)
		{
			Pposition.x -= (vitesse.y - 100) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyD) && Pposition.y > 0)
	{	// Mouvement vers la droite

		frameY = DROITE;
		if (!collision(playerfrect, DROITE, vitesse))
		{
			Pposition.x += vitesse.x * GetDeltaTime();
		}
		else if (collision(playerfrect, DROITE, vitesse) == 2)
		{
			Pposition.x += (vitesse.y - 100) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}

	if (isMoving)									// Si timer > 0.2s on fait l'anim
	{
		if (animTime > 0.08)
		{
			frameX++;											// Incr�mente frameX donc change de frame
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;					// On recalcul la position � gauche du rectangle par rapport � la nouvelle frame
			irect.top = frameY * irect.height;					// M�me chose pour la position haute
			sfSprite_setTextureRect(player, irect);
															// Application sur la texture du sprite de ce rectangle
			animTime = 0.0f;									// Reset animTime
		}
	}
	else													// si on ne bouge pas
	{
		frameX = 0;											// On remet l'animation � la premi�re frame
		irect.left = frameX * irect.width;					// On recalcul la position � gauche du rectangle par rapport � la nouvelle frame
		sfSprite_setTextureRect(player, irect);				// Application sur la texture du sprite de ce rectangle
	}
	updateCam(Pposition);
	
}




void displayPlayer(sfRenderWindow* _window)
{
	// Affichage du joueur
	sfSprite_setPosition(player, Pposition);
	sfRenderWindow_drawSprite(_window, player, NULL);

}

void EditorMod_player()
{	// Editeur | Fonction qui permet de changer la taille et la vitesse du joueur en fonction du mode 
	scale.x = 0.0f;
	scale.y = 0.0f;
	vitesse.x = 2000;
	vitesse.y = 2000;
	sfSprite_setScale(player, scale);
}

void GameMod_player()
{	// Joueur | Fonction qui permet de changer la taille et la vitesse du joueur en fonction du mode
	scale.x = 0.8f;
	scale.y = 0.8f;
	vitesse.x = 200;
	vitesse.y = 200;
	sfSprite_setScale(player, scale);
}



