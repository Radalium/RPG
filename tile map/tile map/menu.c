#include "menu.h"
#include "SFML/Graphics.h"
#include "player.h"

#define TEXTURE_PATH "../Ressources/Textures/"

sfVector2f poslogo = { 200.f, -105.0f };
sfVector2f posjouer = { 400.f, 310.f };
sfVector2f posedit = { 450.f, 460.f };
sfVector2f posquit = { 400.f, 550.f };
sfVector2f posbackground = { -150.0f,0.0f };

sfVector2f scalejouer = { 0.5f,0.5f };
sfVector2f scaleback = { 0.2f,0.2f };
sfVector2f scalelogo = { 0.5f,0.5f };
sfVector2f scaleedit = { 0.75f,0.75f };
sfVector2f scalequit = { 0.5f,0.5f };

sfFloatRect rectjouer;
sfFloatRect rectedit;
sfFloatRect rectquitter;
sfVector2i mousepos;

sfSprite* Logo;
sfSprite* Background;
sfSprite* Bouton_Jouer;
sfSprite* Bouton_Editeur;
sfSprite* Bouton_Quitter;

sfTexture* LogoTexture;
sfTexture* Bouton_JouerTexture;
sfTexture* Bouton_EditeurTexture;
sfTexture* Bouton_QuitterTexture;
sfTexture* Background_Texture;


//sfView menucam;

void initMenu()
{

	Logo = sfSprite_create();
	Bouton_Jouer = sfSprite_create();
	Bouton_Editeur = sfSprite_create();
	Bouton_Quitter = sfSprite_create();
	Background = sfSprite_create();

	LogoTexture = sfTexture_createFromFile(TEXTURE_PATH"logolinkquest.png", NULL);
	Bouton_JouerTexture = sfTexture_createFromFile(TEXTURE_PATH"Jouer.png", NULL);
	Bouton_EditeurTexture = sfTexture_createFromFile(TEXTURE_PATH"EDITER.png", NULL);
	Bouton_QuitterTexture = sfTexture_createFromFile(TEXTURE_PATH"QUITTER.png", NULL);
	Background_Texture = sfTexture_createFromFile(TEXTURE_PATH"background2.jpg", NULL);

	sfSprite_setTexture(Logo, LogoTexture, sfTrue);
	sfSprite_setTexture(Bouton_Jouer, Bouton_JouerTexture, sfTrue);
	sfSprite_setTexture(Bouton_Editeur, Bouton_EditeurTexture, sfTrue);
	sfSprite_setTexture(Bouton_Quitter, Bouton_QuitterTexture, sfTrue);
	sfSprite_setTexture(Background, Background_Texture, sfTrue);

	sfSprite_setOrigin(Logo, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Jouer, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Editeur, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Quitter, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Background, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));

	
	sfSprite_setPosition(Bouton_Jouer, posjouer);
	sfSprite_setPosition(Bouton_Editeur, posedit);
	sfSprite_setPosition(Bouton_Quitter, posquit);
	sfSprite_setPosition(Background, posbackground);

	sfSprite_setScale(Background, scaleback);
	sfSprite_setScale(Bouton_Jouer, scalejouer);
	sfSprite_setScale(Bouton_Editeur, scaleedit);
	sfSprite_setScale(Bouton_Quitter, scalequit);

	rectjouer = sfSprite_getGlobalBounds(Bouton_Jouer);
	rectedit = sfSprite_getGlobalBounds(Bouton_Editeur);
	rectquitter = sfSprite_getGlobalBounds(Bouton_Quitter);

}
float direction_logo = 1.f;
void updateMenu(sfRenderWindow* _window)
{
	poslogo.y += direction_logo;
	if (poslogo.y > -105.0f) direction_logo = -0.002f;
	if (poslogo.y < -115.0f) direction_logo = 0.002f;
	sfSprite_setPosition(Logo, poslogo);

	mousepos = sfMouse_getPositionRenderWindow(_window);

	

	if (sfFloatRect_contains(&rectjouer, mousepos.x, mousepos.y))
	{
		sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			actualState = JOUER;
			GameMod_cam();
			GameMod_player();
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 255));
	}

	if (sfFloatRect_contains(&rectedit, mousepos.x, mousepos.y))
	{
		sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			actualState = EDITEUR;
			EditorMod_cam();
			EditorMod_player();
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 255));
	}

	if (sfFloatRect_contains(&rectquitter, mousepos.x, mousepos.y))
	{
		sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			actualState = QUITTER;
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 255));
	}

	

}

void DisplayMenu(sfRenderWindow* _window)
{
	sfRenderWindow_drawSprite(_window, Background, NULL);
	sfRenderWindow_drawSprite(_window, Logo, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Jouer, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Editeur, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Quitter, NULL);
	

}
