#include "player.h"
#define TEXTURE_PATH "../Ressources/Textures/"
#include"tools.h"
#include"map.h"
#include "musique.h"
#include "cam.h"

sfSprite* player;
sfTexture* playertexture;
sfIntRect irect = { 0, 0, 17, 23 };
sfVector2f scale = { 0.8f,0.8f };
float animTime = 0.0f;
int frameX = 0;
int frameY = 0;
sfBool isMoving = sfFalse;
sfVector2f Pposition = { 340.0f, 340.0f };
sfVector2f vitesse = { 75.0f, 75.0f };

float letemps = 0.0f;

float rayon1;
int chestouverture=0;
void initPlayer()
{
	
	// Initialisation du joueur

	playertexture = sfTexture_createFromFile(TEXTURE_PATH"player.png", NULL);
	player = sfSprite_create();
	sfSprite_setTexture(player, playertexture, sfTrue);
	sfSprite_setScale(player, scale);
	sfSprite_setTextureRect(player, irect);
}

void animpcoffre(i)
{
	frameY = i;
}
void updatePlayer(sfRenderWindow* _window)
{
	// Update du joueur
	sfFloatRect playerfrect = sfSprite_getGlobalBounds(player);
	rayon1 = playerfrect.width*3;

	if (sfKeyboard_isKeyPressed(sfKeyEscape))
	{
		Editor = 0;
		iModeDeJeu = 0;
		actualState = MENU;
		sfMusic_play(menu);
	}

	isMoving = sfFalse;
	if (sfKeyboard_isKeyPressed(sfKeyZ) && Pposition.y >10 && chestouverture == 0)
	{	// Mouvement vers le haut
		frameY = HAUT;
		
		if(!collision(playerfrect, HAUT , vitesse ))
		{
			Pposition.y -= vitesse.y * GetDeltaTime();
		}
		else if (collision(playerfrect, HAUT, vitesse) == 2)
		{
			Pposition.y -= (vitesse.y - 37.5f) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyS) && Pposition.y < 1890 && chestouverture == 0)
	{	// Mouvement vers le bas
		
		frameY = BAS;
		if (!collision(playerfrect, BAS, vitesse))
		{
			Pposition.y += vitesse.y * GetDeltaTime();
		}
		else if (collision(playerfrect, BAS, vitesse) == 2)
		{
			Pposition.y += (vitesse.y-37.5f) * GetDeltaTime();
		}
		
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyQ) && Pposition.x > 10 && chestouverture == 0)
	{	// Mouvement vers la gauche
		
		frameY = GAUCHE;
		if (!collision(playerfrect, GAUCHE, vitesse))
		{
			Pposition.x -= vitesse.x * GetDeltaTime();
		}
		else if (collision(playerfrect, GAUCHE, vitesse) == 2)
		{
			Pposition.x -= (vitesse.y - 37.5f) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}
	else if (sfKeyboard_isKeyPressed(sfKeyD) && Pposition.x < 6390 && chestouverture == 0)
	{	// Mouvement vers la droite
		
		frameY = DROITE;
		if (!collision(playerfrect, DROITE, vitesse))
		{
			Pposition.x += vitesse.x * GetDeltaTime();
		}
		else if (collision(playerfrect, DROITE, vitesse) == 2)
		{
			Pposition.x += (vitesse.y - 37.5f) * GetDeltaTime();
		}
		animTime += GetDeltaTime();
		isMoving = sfTrue;
	}

	if (isMoving)									// Si timer > 0.2s on fait l'anim
	{
		
		if (animTime > 0.08)
		{
			frameX++;											// Incrémente frameX donc change de frame
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;					// On recalcul la position à gauche du rectangle par rapport à la nouvelle frame
			irect.top = frameY * irect.height;					// Même chose pour la position haute
			sfSprite_setTextureRect(player, irect);
															// Application sur la texture du sprite de ce rectangle
			animTime = 0.0f;									// Reset animTime
		}
	}
	else											// si on ne bouge pas
	{
		frameX = 0;											// On remet l'animation à la première frame
		irect.left = frameX * irect.width;	
		irect.top = frameY * irect.height;					// On recalcul la position à gauche du rectangle par rapport à la nouvelle frame
		sfSprite_setTextureRect(player, irect);				// Application sur la texture du sprite de ce rectangle
	}
	updateCam(Pposition);

	if (isMoving == sfTrue && actualState == JOUER)
	{
		if (letemps > 0.4f )
		{
			sfSound_play(pas);
			letemps = 0.0f;
		}
	}
	letemps += GetDeltaTime();
	
}




void displayPlayer(sfRenderWindow* _window)
{
	// Affichage du joueur
	sfSprite_setPosition(player, Pposition);
	sfRenderWindow_drawSprite(_window, player, NULL);

}


void EditorMod_player()
{
	
	
	// Editeur | Fonction qui permet de changer la taille et la vitesse du joueur en fonction du mode 
	scale.x = 0.0f;
	scale.y = 0.0f;
	vitesse.x = 2000.f;
	vitesse.y = 2000.f;
	sfSprite_setScale(player, scale);
}


void GameMod_player()
{
	

	// Joueur | Fonction qui permet de changer la taille et la vitesse du joueur en fonction du mode
	scale.x = 0.8f;
	scale.y = 0.8f;
	vitesse.x = 75.f;
	vitesse.y = 75.f;
	sfSprite_setScale(player, scale);
}

void Vplus()
{
	if (vitesse.x < 4000)
	{
		vitesse.x = vitesse.x * 1.1f;
		vitesse.y = vitesse.y * 1.1f;
	}
}

void Vmoins()
{
	if (vitesse.x < 75)
	{
		vitesse.x = vitesse.x * 0.9f;
		vitesse.y = vitesse.y * 0.9f;
	}
}


sfBool CalculD(sfVector2f _pos1, float _rayon2)
{
		if ((_pos1.x - Pposition.x) * (_pos1.x - Pposition.x) + (_pos1.y - Pposition.y) * (_pos1.y - Pposition.y) < (rayon1 + _rayon2) * (rayon1 + _rayon2))
		{
			return sfTrue;
		}
		else return sfFalse;	
}

void couv(int _chestouvert)
{
	if (_chestouvert == 0)
	{
		chestouverture = 0;
	}
	else
	{
		chestouverture = 1;
	}
}
