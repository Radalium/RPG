#include "NPC.h"
#define TEXTURE_PATH "../Ressources/Textures/"
#include"tools.h"
#include"map.h"


sfSprite* NPC;
sfTexture* NPCTexture;
sfIntRect NPCrect = { 0, 0, 16, 22 };
sfVector2f NPCscale = { 0.8f,0.8f };
float NPCanimTime = 0.0f;
int NframeX = 0;
sfBool isTalking = sfFalse;
sfVector2f NPCpos = { 340.0f, 340.0f };
int parle = 0;

void initNPC()
{
	// Initialisation du NPC
	NPCTexture = sfTexture_createFromFile(TEXTURE_PATH"princesse.png", NULL);
	NPC = sfSprite_create();
	sfSprite_setTexture(NPC, NPCTexture, sfTrue);
	sfSprite_setScale(NPC, NPCscale);
	sfSprite_setTextureRect(NPC, NPCrect);
}

void updateNPC(sfRenderWindow* _window)
{
	// Update du NPC
	sfFloatRect playerfrect = sfSprite_getGlobalBounds(NPC);

	isTalking = sfFalse;
	if (sfKeyboard_isKeyPressed(sfKeyV))
	{	// elle parle
		NPCanimTime += GetDeltaTime();
		isTalking = sfTrue;

	}
	if (isTalking)												// Si timer > 0.2s on fait l'anim
	{
		if (NPCanimTime > 0.08)
		{
			NframeX++;											// Incrémente frameX donc change de frame
			if (NframeX > 1) NframeX = 0;
			NPCrect.left = NframeX * NPCrect.width;				// On recalcul la position à gauche du rectangle par rapport à la nouvelle frame
			NPCrect.top = 0 * NPCrect.height;					// Même chose pour la position haute
			sfSprite_setTextureRect(NPC, NPCrect);
																// Application sur la texture du sprite de ce rectangle
			NPCanimTime = 0.0f;									// Reset animTime
		}
	}
}

void DisplayNPC(sfRenderWindow* _window)
{
	sfSprite_setPosition(NPC, NPCpos);
	sfRenderWindow_drawSprite(_window, NPC, NULL);
}
