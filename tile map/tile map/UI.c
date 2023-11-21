#include "UI.h"
#include "tools.h"

// Initialisation des variables
sfSprite* Cle0;
sfSprite* Cle1;
sfSprite* Cle2;
sfSprite* Cle3;

sfTexture* Cle0Texture;
sfTexture* Cle1Texture;
sfTexture* Cle2Texture;
sfTexture* Cle3Texture;

sfVector2f Cle0pos = { 160.f,60.f };
sfVector2f Cle1pos = { 160.f,60.f };
sfVector2f Cle2pos = { 150.f,50.f };
sfVector2f Cle3pos = { 150.f,50.f };

sfVector2f Cle0scale = { 0.80f,0.80f };
sfVector2f Cle1scale = { 0.80f,0.80f };
sfVector2f Cle2scale = { 0.80f,0.80f };
sfVector2f Cle3scale = { 0.80f,0.80f };
	

float temps;

void initUI()
{ // Initialisation des sprites et textures
		nmcle = 0;
		Cle0 = sfSprite_create();
		Cle1 = sfSprite_create();
		Cle2 = sfSprite_create();
		Cle3 = sfSprite_create();

		Cle0Texture = sfTexture_createFromFile("../Ressources/Textures/artefact1.png", NULL);
		Cle1Texture = sfTexture_createFromFile("../Ressources/Textures/artefact2.png", NULL);
		Cle2Texture = sfTexture_createFromFile("../Ressources/Textures/artefact3.png", NULL);
		Cle3Texture = sfTexture_createFromFile("../Ressources/Textures/artefact4.png", NULL);

		sfSprite_setOrigin(Cle0, vector2f(sfSprite_getGlobalBounds(Cle0).width / 2, sfSprite_getGlobalBounds(Cle0).height / 2));
		sfSprite_setOrigin(Cle1, vector2f(sfSprite_getGlobalBounds(Cle1).width / 2, sfSprite_getGlobalBounds(Cle1).height / 2));
		sfSprite_setOrigin(Cle2, vector2f(sfSprite_getGlobalBounds(Cle2).width / 2, sfSprite_getGlobalBounds(Cle2).height / 2));
		sfSprite_setOrigin(Cle3, vector2f(sfSprite_getGlobalBounds(Cle3).width / 2, sfSprite_getGlobalBounds(Cle3).height / 2));

		sfSprite_setTexture(Cle0, Cle0Texture, sfTrue);
		sfSprite_setTexture(Cle1, Cle1Texture, sfTrue);
		sfSprite_setTexture(Cle2, Cle2Texture, sfTrue);
		sfSprite_setTexture(Cle3, Cle3Texture, sfTrue);

		sfSprite_setPosition(Cle0, Cle0pos);
		sfSprite_setPosition(Cle1, Cle1pos);
		sfSprite_setPosition(Cle2, Cle2pos);
		sfSprite_setPosition(Cle3, Cle3pos);

		sfSprite_setScale(Cle0, Cle0scale);
		sfSprite_setScale(Cle1, Cle1scale);
		sfSprite_setScale(Cle2, Cle2scale);
		sfSprite_setScale(Cle3, Cle3scale);
	

}
// Fonction qui permet de mettre a jour les sprites
temps = 0;
void updateUI(sfVector2f _playerpos)
{
	// Update des sprites en fonction du nombre de cle
	temps += GetDeltaTime();
	if (sfKeyboard_isKeyPressed(sfKeyY) && temps > 0.1f)
	{
		nmcle++;
		temps = 0.f;
	}

	if (nmcle == 0)
	{
		Cle0pos.x = _playerpos.x - 97.f;
		Cle0pos.y = _playerpos.y - 72.f;

		sfSprite_setPosition(Cle0, Cle0pos);
	}
	if (nmcle == 1)
	{
		Cle1pos.x = _playerpos.x - 97.f;
		Cle1pos.y = _playerpos.y - 72.f;

		sfSprite_setPosition(Cle1, Cle1pos);
	}
	if (nmcle == 2)
	{
		Cle2pos.x = _playerpos.x - 97.f;
		Cle2pos.y = _playerpos.y - 72.f;

		sfSprite_setPosition(Cle2, Cle2pos);
	}
	if (nmcle == 3)
	{
		Cle3pos.x = _playerpos.x - 97.f; 
		Cle3pos.y = _playerpos.y - 72.f;

		sfSprite_setPosition(Cle3, Cle3pos);
	}
}


void displayUI(sfRenderWindow* _window, sfView* _cam)
{	// Affichage des sprites en fonction du nombre de cle
	if (nmcle == 1)
	{
		sfRenderWindow_drawSprite(_window, Cle0, NULL);
	}
	if (nmcle == 2)
	{
		sfRenderWindow_drawSprite(_window, Cle1, NULL);
	}
	if (nmcle == 3)
	{
		sfRenderWindow_drawSprite(_window, Cle2, NULL);
	}
	if (nmcle == 4)
	{
		sfRenderWindow_drawSprite(_window, Cle3, NULL);
	}
}