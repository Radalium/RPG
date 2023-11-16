#include "menu.h"
#include "SFML/Graphics.h"
#include "player.h"
#include "musique.h"

#define TEXTURE_PATH "../Ressources/Textures/"

// Initalisation des variables globales

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

sfView* menucam;
sfVector2f menurectcam = { 800.f ,600.f };

void initMenu()
{
	// Initialisation de la view
	menucam = sfView_create();
	sfView_setSize(menucam, menurectcam);

	// initialisation des sprites
	Logo = sfSprite_create();
	Bouton_Jouer = sfSprite_create();
	Bouton_Editeur = sfSprite_create();
	Bouton_Quitter = sfSprite_create();
	Background = sfSprite_create();


	// initialisation des textures
	LogoTexture = sfTexture_createFromFile(TEXTURE_PATH"logolinkquest.png", NULL);
	Bouton_JouerTexture = sfTexture_createFromFile(TEXTURE_PATH"Jouer.png", NULL);
	Bouton_EditeurTexture = sfTexture_createFromFile(TEXTURE_PATH"EDITER.png", NULL);
	Bouton_QuitterTexture = sfTexture_createFromFile(TEXTURE_PATH"QUITTER.png", NULL);
	Background_Texture = sfTexture_createFromFile(TEXTURE_PATH"background2.jpg", NULL);

	// Application des textures aux sprites
	sfSprite_setTexture(Logo, LogoTexture, sfTrue);
	sfSprite_setTexture(Bouton_Jouer, Bouton_JouerTexture, sfTrue);
	sfSprite_setTexture(Bouton_Editeur, Bouton_EditeurTexture, sfTrue);
	sfSprite_setTexture(Bouton_Quitter, Bouton_QuitterTexture, sfTrue);
	sfSprite_setTexture(Background, Background_Texture, sfTrue);

	// Placement du point d'origine des sprites
	sfSprite_setOrigin(Logo, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Jouer, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Editeur, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Quitter, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Background, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));

	// Placement des sprites
	sfSprite_setPosition(Bouton_Jouer, posjouer);
	sfSprite_setPosition(Bouton_Editeur, posedit);
	sfSprite_setPosition(Bouton_Quitter, posquit);
	sfSprite_setPosition(Background, posbackground);

	// Mise à l'échelle des sprites
	sfSprite_setScale(Background, scaleback);
	sfSprite_setScale(Bouton_Jouer, scalejouer);
	sfSprite_setScale(Bouton_Editeur, scaleedit);
	sfSprite_setScale(Bouton_Quitter, scalequit);

	// Récupération des rectangles de collision
	rectjouer = sfSprite_getGlobalBounds(Bouton_Jouer);
	rectedit = sfSprite_getGlobalBounds(Bouton_Editeur);
	rectquitter = sfSprite_getGlobalBounds(Bouton_Quitter);
	sfMusic_play(menu);
}
float direction_logo = 1.f;
void updateMenu(sfRenderWindow* _window)
{
	// Mouvement du logo
	
	poslogo.y += direction_logo;
	if (poslogo.y > -105.0f ) direction_logo = -0.002f ;
	if (poslogo.y < -115.0f) direction_logo = 0.002f;
	sfSprite_setPosition(Logo, poslogo);

	// Récupération de la position de la souris
	mousepos = sfMouse_getPositionRenderWindow(_window);

	
	// Detection si la souris est sur le bloc
	if (sfFloatRect_contains(&rectjouer, mousepos.x, mousepos.y))
	{	
		sfSound_play(menu2);
		sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			// Changement du statut de jeu
			actualState = JOUER;
			GameMod_cam();
			GameMod_player();
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 255));
	}

	// Detection si la souris est sur le bloc
	if (sfFloatRect_contains(&rectedit, mousepos.x, mousepos.y))
	{
		sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			// Changement du statut de jeu
			actualState = EDITEUR;
			EditorMod_cam();
			EditorMod_player();
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 255));
	}

	// Detection si la souris est sur le bloc
	if (sfFloatRect_contains(&rectquitter, mousepos.x, mousepos.y))
	{
		sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 200));
		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			// Changement du statut de jeu
			actualState = QUITTER;
		}
	}
	else
	{
		sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 255));
	}

	sfView_setCenter(menucam,vector2f(400.f,300.f));

}

void DisplayMenu(sfRenderWindow* _window)
{
	// Affichage des boutons / logo / background
	sfRenderWindow_drawSprite(_window, Background, NULL);
	sfRenderWindow_drawSprite(_window, Logo, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Jouer, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Editeur, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Quitter, NULL);
	sfRenderWindow_setView(_window, menucam);
	

}
