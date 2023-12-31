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
sfVector2f possonplus = { 370.f, 630.f };
sfVector2f possonmoins = { 250.f, 630.f };
sfVector2f posbackground = { -150.0f,0.0f };
sfVector2f posspointintero = { 750.f,560.f };
sfVector2f possfondtouche = { 400.f,300.f };
sfVector2f posstexte = { 130.0f,550.f };

sfVector2f scalejouer = { 0.5f,0.5f };
sfVector2f scaleback = { 0.2f,0.2f };
sfVector2f scalelogo = { 0.5f,0.5f };
sfVector2f scaleedit = { 0.75f,0.75f };
sfVector2f scalequit = { 0.5f,0.5f };
sfVector2f scalsonplus = { 1.f,1.f };
sfVector2f scalsonmoins = { 1.f,1.f };
sfVector2f scalepointintero = { 0.25f,0.25f };
sfVector2f scalefondtouche = { 1.f,1.f };

sfFloatRect rectjouer;
sfFloatRect rectedit;
sfFloatRect rectquitter;
sfFloatRect rectsonplus;
sfFloatRect rectsonmoins;
sfFloatRect rectpointintero;

sfVector2i mousepos;

sfSprite* Logo;
sfSprite* Background;
sfSprite* Bouton_Jouer;
sfSprite* Bouton_Editeur;
sfSprite* Bouton_Quitter;
sfSprite* Sonplus;
sfSprite* Sonmoins;
sfSprite* pointintero;
sfSprite* fondtouche;

sfTexture* LogoTexture;
sfTexture* Bouton_JouerTexture;
sfTexture* Bouton_EditeurTexture;
sfTexture* Bouton_QuitterTexture;
sfTexture* Background_Texture;
sfTexture* SonplusTexture;
sfTexture* SonmoinsTexture;
sfTexture* pointinteroTexture;
sfTexture* fondtoucheTexture;
sfText* text2;
sfFont* font2;


int demandetouches = 0; 

sfView* menucam;
sfVector2f menurectcam = { 800.f ,600.f };
float timermusique, timermusique1, timermusique2, timermusique3, timermusique4, timermusique5, timermusique6, timermusique7, timermusique8 = 0.f;

char volchar[4] = "50";


void initMenu()
{
	// Init du texte de volume

	text2 = sfText_create();
	font2 = sfFont_createFromFile("..//Ressources//Fonts//3Dventure.ttf", NULL);

	sfText_setFont(text2, font2);
	sprintf(volchar, "%d", volume);
	sfText_setString(text2, volchar);
	sfText_setPosition(text2, posstexte);


	// Initialisation de la view
	menucam = sfView_create();
	sfView_setSize(menucam, menurectcam);

	// initialisation des sprites
	Logo = sfSprite_create();
	Bouton_Jouer = sfSprite_create();
	Bouton_Editeur = sfSprite_create();
	Bouton_Quitter = sfSprite_create();
	Background = sfSprite_create();
	Sonplus = sfSprite_create();
	Sonmoins = sfSprite_create();
	
	pointintero = sfSprite_create();
	fondtouche = sfSprite_create();


	// initialisation des textures
	LogoTexture = sfTexture_createFromFile(TEXTURE_PATH"logolinkquest.png", NULL);
	Bouton_JouerTexture = sfTexture_createFromFile(TEXTURE_PATH"Jouer.png", NULL);
	Bouton_EditeurTexture = sfTexture_createFromFile(TEXTURE_PATH"EDITER.png", NULL);
	Bouton_QuitterTexture = sfTexture_createFromFile(TEXTURE_PATH"QUITTER.png", NULL);
	Background_Texture = sfTexture_createFromFile(TEXTURE_PATH"background2.jpg", NULL);
	SonplusTexture = sfTexture_createFromFile(TEXTURE_PATH"sonplus.png", NULL);
	SonmoinsTexture = sfTexture_createFromFile(TEXTURE_PATH"sonmoins.png", NULL);
	pointinteroTexture = sfTexture_createFromFile(TEXTURE_PATH"pointintero.png", NULL);
	fondtoucheTexture = sfTexture_createFromFile(TEXTURE_PATH"touche.png", NULL);

	// Application des textures aux sprites
	sfSprite_setTexture(Logo, LogoTexture, sfTrue);
	sfSprite_setTexture(Bouton_Jouer, Bouton_JouerTexture, sfTrue);
	sfSprite_setTexture(Bouton_Editeur, Bouton_EditeurTexture, sfTrue);
	sfSprite_setTexture(Bouton_Quitter, Bouton_QuitterTexture, sfTrue);
	sfSprite_setTexture(Background, Background_Texture, sfTrue);
	sfSprite_setTexture(Sonmoins, SonmoinsTexture, sfTrue);
	sfSprite_setTexture(Sonplus, SonplusTexture, sfTrue);
	sfSprite_setTexture(pointintero, pointinteroTexture, sfTrue);
	sfSprite_setTexture(fondtouche, fondtoucheTexture, sfTrue);

	// Placement du point d'origine des sprites
	sfSprite_setOrigin(Logo, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Jouer, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Editeur, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Bouton_Quitter, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Background, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Sonmoins, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(Sonplus, vector2f(sfSprite_getGlobalBounds(Bouton_Jouer).width / 2, sfSprite_getGlobalBounds(Bouton_Jouer).height / 2));
	sfSprite_setOrigin(pointintero, vector2f(sfSprite_getGlobalBounds(pointintero).width / 2, sfSprite_getGlobalBounds(pointintero).height / 2));
	sfSprite_setOrigin(fondtouche, vector2f(sfSprite_getGlobalBounds(fondtouche).width / 2, sfSprite_getGlobalBounds(fondtouche).height / 2));

	// Placement des sprites
	sfSprite_setPosition(Bouton_Jouer, posjouer);
	sfSprite_setPosition(Bouton_Editeur, posedit);
	sfSprite_setPosition(Bouton_Quitter, posquit);
	sfSprite_setPosition(Background, posbackground);
	sfSprite_setPosition(Sonplus, possonplus);
	sfSprite_setPosition(Sonmoins, possonmoins);
	sfSprite_setPosition(pointintero, posspointintero);
	sfSprite_setPosition(fondtouche, possfondtouche);

	// Mise � l'�chelle des sprites
	sfSprite_setScale(Background, scaleback);
	sfSprite_setScale(Bouton_Jouer, scalejouer);
	sfSprite_setScale(Bouton_Editeur, scaleedit);
	sfSprite_setScale(Bouton_Quitter, scalequit);
	sfSprite_setScale(Sonplus, scalsonplus);
	sfSprite_setScale(Sonmoins, scalsonmoins);
	sfSprite_setScale(pointintero, scalepointintero);


	// R�cup�ration des rectangles de collision
	rectjouer = sfSprite_getGlobalBounds(Bouton_Jouer);
	rectedit = sfSprite_getGlobalBounds(Bouton_Editeur);
	rectquitter = sfSprite_getGlobalBounds(Bouton_Quitter);
	rectsonplus = sfSprite_getGlobalBounds(Sonplus);
	rectsonmoins = sfSprite_getGlobalBounds(Sonmoins);
	rectpointintero = sfSprite_getGlobalBounds(pointintero);
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

	// R�cup�ration de la position de la souris
	mousepos = sfMouse_getPositionRenderWindow(_window);
	

	
	if (demandetouches == 0)
	{// Detection si la souris est sur le bloc
		if (sfFloatRect_contains(&rectjouer, mousepos.x, mousepos.y))
		{
			if (timermusique > 0.15f)
			{
				sfSound_play(menu2);
				timermusique = 0.f;
			}

			sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 200));
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{

				// Changement du statut de jeu
				actualState = JOUER;
				Position_joueur();
				Position_NPC();
				GameMod_cam();
				GameMod_player();
				sfMusic_play(forest);
			}
		}
		else
		{
			timermusique += GetDeltaTime();
			sfSprite_setColor(Bouton_Jouer, sfColor_fromRGBA(255, 255, 255, 255));
		}

		// Detection si la souris est sur le bloc
		if (sfFloatRect_contains(&rectedit, mousepos.x, mousepos.y))
		{
			if (timermusique1 > 0.15f)
			{
				sfSound_play(menu2);
				timermusique1 = 0.f;
			}

			sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 200));
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				// Changement du statut de jeu
				actualState = EDITEUR;
				EditorMod_cam();
				EditorMod_player();
				sfMusic_play(editeur);
			}
		}
		else
		{
			timermusique1 += GetDeltaTime();
			sfSprite_setColor(Bouton_Editeur, sfColor_fromRGBA(255, 255, 255, 255));
		}

		// Detection si la souris est sur le bloc
		if (sfFloatRect_contains(&rectquitter, mousepos.x, mousepos.y))
		{
			if (timermusique2 > 0.15f)
			{
				sfSound_play(menu2);
				timermusique2 = 0.f;
			}

			sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 200));
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				// Changement du statut de jeu
				actualState = QUITTER;
			}
		}
		else
		{
			timermusique2 += GetDeltaTime();
			sfSprite_setColor(Bouton_Quitter, sfColor_fromRGBA(255, 255, 255, 255));
		}

		// Detection si la souris est sur le bloc
		if (sfFloatRect_contains(&rectsonplus, mousepos.x, mousepos.y))
		{
			if (timermusique3 > 0.15f)
			{ // Joue le son menu2
				sfSound_play(menu2);
				timermusique3 = 0.f;
			}
			sfSprite_setColor(Sonplus, sfColor_fromRGBA(255, 255, 255, 200));
			if (sfMouse_isButtonPressed(sfMouseLeft) && volume < 100)
			{
				// Si le bouton gauche de la souris est preser et que le volume est inferieur a 100 cela augmente le volume
				if (timermusique5 > 0.1f)
				{

					volume += 10;
					timermusique5 = 0.f;
					sprintf(volchar, "%d", volume);
					sfText_setString(text2, volchar);
				}
			}
		}
		else
		{
			timermusique3 += GetDeltaTime();
			sfSprite_setColor(Sonplus, sfColor_fromRGBA(255, 255, 255, 255));
		}

		timermusique5 += GetDeltaTime();

		if (sfFloatRect_contains(&rectpointintero, mousepos.x, mousepos.y))
		{
			if (timermusique7 > 0.15f)
			{ // Joue le son menu2
				sfSound_play(menu2);
				timermusique7 = 0.f;
			}
			sfSprite_setColor(pointintero, sfColor_fromRGBA(255, 255, 255, 200));

			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				if (timermusique8 > 0.15f)
				{
					demandetouches = 1;
					timermusique8 = 0.f;
				}
			}
		}
		else
		{
			timermusique7 += GetDeltaTime();
			sfSprite_setColor(Sonplus, sfColor_fromRGBA(255, 255, 255, 255));
		}
		timermusique8 += GetDeltaTime();

		// Detection si la souris est sur le bloc
		if (sfFloatRect_contains(&rectsonmoins, mousepos.x, mousepos.y))
		{
			if (timermusique4 > 0.15f)
			{ // Joue le son menu2
				sfSound_play(menu2);
				timermusique4 = 0.f;
			}

			sfSprite_setColor(Sonmoins, sfColor_fromRGBA(255, 255, 255, 200));
			if (sfMouse_isButtonPressed(sfMouseLeft) && volume > 0)
			{// Si le bouton gauche de la souris est preser et que le volume est superieur a 0 cela diminue le volume
				if (timermusique6 > 0.1f)
				{
					volume -= 10;
					timermusique6 = 0.f;
					sprintf(volchar, "%d", volume);
					sfText_setString(text2, volchar);
				}
			}
		}
		else
		{
			timermusique4 += GetDeltaTime();

			sfSprite_setColor(Sonmoins, sfColor_fromRGBA(255, 255, 255, 255));
		}
		timermusique6 += GetDeltaTime();
	}
	if (sfKeyboard_isKeyPressed(sfKeyEscape))
	{
		demandetouches = 0;
	}

	sfView_setCenter(menucam,vector2f(400.f,300.f));

}

void DisplayMenu(sfRenderWindow* _window)
{
	// Affichage des boutons / logo / background
	if (demandetouches == 0)
	{
	
	sfRenderWindow_drawSprite(_window, Background, NULL);
	sfRenderWindow_drawSprite(_window, Logo, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Jouer, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Editeur, NULL);
	sfRenderWindow_drawSprite(_window, Bouton_Quitter, NULL);
	sfRenderWindow_drawSprite(_window, Sonplus, NULL);
	sfRenderWindow_drawSprite(_window, Sonmoins, NULL);
	sfRenderWindow_drawSprite(_window, pointintero, NULL);
	sfRenderWindow_drawText(_window, text2, NULL);
	}
	if (demandetouches == 1)
	{
		sfRenderWindow_drawSprite(_window, fondtouche, NULL);
	}
	sfRenderWindow_setView(_window, menucam);
	

}


