#include "map.h"
#include "tools.h"
#include "player.h"
#include "musique.h"
#include "UI.h"

#define TEXTURE_PATH "../Ressources/Textures/"

sfSprite* background1;
sfTexture* backtexture1;
sfVector2f backpos;
sfVector2f portedefinpos;

typedef enum coffre
{
	BLEU,
	VERTE,
	ROUGE
}statuecoffre;


statuecoffre coffstat = -1;

typedef enum portefin
{
	FERMEE,
	PLACEMENTORBE,
	OUVERTE
};

sfIntRect irectporte = { 0,0, 32,32 };

typedef struct Cchest Cchest;
struct Cchest
{	
	sfSprite* chest;
	sfTexture* chesttexture;
	sfIntRect chestrect;
	sfVector2f chestpos;
	int ChestState;
};
Cchest ch[3];
int blocage_coffre = 0;
int nombrecoffre;
int NChest=0;
float CRayon = 16;

int nombre_NPC = 0;
int nombre_joueur = 0;
sfSprite* FragmentedOrb;
sfTexture* FragmentedOrbTexture;
sfIntRect FragmentedOrbrect = {0,0,22,22};
sfVector2f FragmentedOrbPos;
int frameY1=0;


sfSprite* tileSprite;
sfTexture* tileTexture;
sfIntRect tileRect;
sfVector2f position = { 0.0f ,0.0f };
sfVector2i Tposition = { 0 ,0 };
int ntile = 0;
float timer_c = 0.0f;
float timer_c2 = 0.0f;

FILE* fichier;

char map[60][200];


//sfSprite* chest;
//sfTexture* chesttexture;
//sfIntRect chestrect;
//sfVector2f chestpos;
float timeouverture = 0.f;
sfBool ouverture = sfFalse;

sfVector2f posorbebleu = { 0.0f,0.0f };
sfVector2f posorberouge = { 0.0f,0.0f };
sfVector2f posorbeverte = { 0.0f,0.0f };

sfVector2f scaleorbebleu = { 0.5f,0.5f };
sfVector2f scaleorberouge = { 0.5f,0.5f };
sfVector2f scaleorbeverte = { 0.5f,0.5f };



sfBool isAnimated = sfFalse;

void initMap()
{
	// Initialisation des variables
	orbebleu = sfSprite_create();
	orberouge = sfSprite_create();
	orbeverte = sfSprite_create();
	porteanim = sfSprite_create();
	portedefin = sfSprite_create();

	textureorbebleu = sfTexture_createFromFile(TEXTURE_PATH"orbebleu.png", NULL);
	textureorberouge = sfTexture_createFromFile(TEXTURE_PATH"orberouge.png", NULL);
	textureorbeverte = sfTexture_createFromFile(TEXTURE_PATH"orbeverte.png", NULL);
	textureporteanim = sfTexture_createFromFile(TEXTURE_PATH"porteanim.png", NULL);
	textureportedefin = sfTexture_createFromFile(TEXTURE_PATH"porte.png", NULL);


	sfSprite_setTexture(orbebleu, textureorbebleu, sfTrue);
	sfSprite_setTexture(orberouge, textureorberouge, sfTrue);
	sfSprite_setTexture(orbeverte, textureorbeverte, sfTrue);
	sfSprite_setTexture(porteanim, textureporteanim, sfTrue);
	sfSprite_setTexture(portedefin, textureportedefin, sfTrue);

	sfSprite_setOrigin(orbebleu, vector2f(sfSprite_getGlobalBounds(orbebleu).width / 2, sfSprite_getGlobalBounds(orbebleu).height / 2));
	sfSprite_setOrigin(orberouge, vector2f(sfSprite_getGlobalBounds(orberouge).width / 2, sfSprite_getGlobalBounds(orberouge).height / 2));
	sfSprite_setOrigin(orbeverte, vector2f(sfSprite_getGlobalBounds(orbeverte).width / 2, sfSprite_getGlobalBounds(orbeverte).height / 2));
	//sfSprite_setOrigin(porteanim, vector2f(sfSprite_getGlobalBounds(porteanim).width / 2, sfSprite_getGlobalBounds(porteanim).height / 2));
	sfSprite_setOrigin(porte, vector2f(sfSprite_getGlobalBounds(porte).width / 2, sfSprite_getGlobalBounds(porte).height / 2));

	sfSprite_setScale(orbebleu, scaleorbebleu);
	sfSprite_setScale(orberouge, scaleorberouge);
	sfSprite_setScale(orbeverte, scaleorbeverte);


	// Initialisation de la map | ouverture du fichier MAP.bin et lecture du contenu dans le tableau map 
	fichier = fopen("MAP1.bin", "r");
	fread(map, sizeof(char), 15000, fichier);
	fclose(fichier);
	fichier = fopen("MAP2.bin", "r");
	fclose(fichier);
	fichier = fopen("MAP3.bin", "r");
	fclose(fichier);
	fichier = fopen("MAPBonus.bin", "r");
	fclose(fichier);




	FragmentedOrb = sfTexture_createFromFile(TEXTURE_PATH"Fragmented_Orb.png", NULL);
	FragmentedOrb = sfSprite_create();
	sfSprite_setTexture(FragmentedOrb, FragmentedOrbTexture, sfTrue);


	tileRect.left = 32;
	tileRect.top = 0;
	tileRect.width = 32;
	tileRect.height = 32;
 	// Initialisation coffre 
	
	for (int i = 0; i < 3; i++)
	{
	ch[i].chesttexture = sfTexture_createFromFile(TEXTURE_PATH"coffre32.png", NULL);
	ch[i].chest = sfSprite_create();
	sfSprite_setTexture(ch[i].chest, ch[i].chesttexture, sfTrue);
	sfSprite_setTextureRect(ch[i].chest, ch[i].chestrect);
	}
	for (int y = 0; y < 3; y++)
	{
		ch[y].chestrect.left = 0;
		ch[y].chestrect.top = 0;
		ch[y].chestrect.width = 32;
		ch[y].chestrect.height = 32;
	}
	

	// Initialisation tileset
	tileTexture = sfTexture_createFromFile(TEXTURE_PATH"tileset.png", NULL);
	tileSprite = sfSprite_create();
	sfSprite_setTexture(tileSprite, tileTexture, sfTrue);

	
	backtexture1 = sfTexture_createFromFile(TEXTURE_PATH"backgroundmine.png", NULL);
	background1 = sfSprite_create();
	sfSprite_setTexture(background1, backtexture1, sfTrue);


	tileRect.left = 32;
	tileRect.top = 0;
	tileRect.width = 32;
	tileRect.height = 32;
}



int blocage = 0;
int numerochest;
int coffre = 0;
float timer2 = 0.0f;
float timer = 0.0f;
int TailleBrush = 0;
float timer_coffre = 0.f;

int combien_de_coffre()
{
		nombrecoffre = 0;
		for (int y = 0; y < 60; y++)
		{
			for (int x = 0; x < 200; x++)
			{
				if (map[y][x] == 5) nombrecoffre++;
			}
		}
		return nombrecoffre;
}
int combien_de_PNJ()
{
	nombre_NPC = 0;
	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			if (map[y][x] == 7) nombre_NPC++;
		}
	}
	return nombre_NPC;
}
int combien_de_joueur()
{
	nombre_joueur = 0;
	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			if (map[y][x] == 9) nombre_joueur++;
		}
	}
	return nombre_joueur;
}

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


	// Gestion de l'édition de la map
	if (iModeDeJeu == 1)
	{


		timer += GetDeltaTime();
		blocage_coffre = 0;
		// Affichage du mode édition pour la map 
		if (mousePosition.x < 800 && mousePosition.y < 600 && mousePosition.x>0 && mousePosition.y>0)
		{
			// Si le bouton gauche de la souris est presser alors on change la case de la map
			if (sfMouse_isButtonPressed(sfMouseLeft) && timer > 0.2f)
			{
				// Gestion de la taille du pinceau 1x1
				timer = 0.f;
				if (TailleBrush == 0 )
				{
					if (ntile == 5)
					{
						if(combien_de_coffre() <3)map[Tposition.y][Tposition.x] = ntile;
					}
					else if (ntile == 7)
					{
						if(combien_de_PNJ() < 1 )map[Tposition.y][Tposition.x] = ntile;
					}
					else if (ntile == 9)
					{
						if (combien_de_joueur() < 1)map[Tposition.y][Tposition.x] = ntile;
					}
					else map[Tposition.y][Tposition.x] = ntile;
				}
				if (TailleBrush == 1 && ntile != 5)
				{	
						// Gestion de la taille du pinceau 3x3
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
				if (TailleBrush == 2)
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
					map [Tposition.y+2][Tposition.x] = ntile;
					map[Tposition.y - 2][Tposition.x] = ntile;
					map[Tposition.y][Tposition.x + 2] = ntile;
					map[Tposition.y][Tposition.x - 2] = ntile;
					map[Tposition.y + 2][Tposition.x + 2] = ntile;
					map[Tposition.y + 2][Tposition.x - 2] = ntile;
					map[Tposition.y - 2][Tposition.x + 2] = ntile;
					map[Tposition.y - 2][Tposition.x - 2] = ntile;
					map[Tposition.y+2][Tposition.x+1] = ntile;
					map[Tposition.y+2][Tposition.x-1] = ntile;
					map[Tposition.y-2][Tposition.x+1] = ntile;
					map[Tposition.y-2][Tposition.x-1] = ntile;
					map[Tposition.y+1][Tposition.x+2] = ntile;
					map[Tposition.y+1][Tposition.x-2] = ntile;
					map[Tposition.y-1][Tposition.x+2] = ntile;
					map[Tposition.y-1][Tposition.x-2] = ntile;

				}
			}
		}

		// Si le bouton droit de la souris est pressée alors on change ntile 
		if (sfMouse_isButtonPressed(sfMouseRight) && timer > 0.5f)
		{
			timer = 0.0f;
			ntile++;
			if (ntile > 46)
				ntile = 0;
		}
		if (sfKeyboard_isKeyPressed(sfKeySpace) && timer > 0.5f)
		{
			timer = 0.0f;
			ntile--;
			if (ntile < 0)
				ntile = 46;
		}
		// Si la touche I est pressée alors on change la taille du pinceau
		if (sfKeyboard_isKeyPressed(sfKeyI) && timer > 0.3f)
		{
			timer = 0.0f;
			TailleBrush = (1 + TailleBrush) % 3;
		}

		// Si la touche M est pressée alors on sauvegarde la map
		if (sfKeyboard_isKeyPressed(sfKeyM) && timer > 0.1f)
		{
			fichier = fopen("MAP1.bin", "w");
			fwrite(map, sizeof(char), 15000, fichier);
			fclose(fichier);
		}

		// Si la touche 1 est pressée alors on charge la map 1
		if (sfKeyboard_isKeyPressed(sfKeyNum1) && timer > 0.8f)
		{
			fichier = fopen("MAP1.bin", "r");
			fread(map, sizeof(char), 15000, fichier);
			fclose(fichier);
		}

		// Si la touche 2 est pressée alors on charge la map 2
		if (sfKeyboard_isKeyPressed(sfKeyNum2)&& timer >0.8f)
		{
			fichier = fopen("MAP2.bin", "r");
			fread(map, sizeof(char), 15000, fichier);
			fclose(fichier);
		}

		// Si la touche 3 est pressée alors on charge la map 3
		if (sfKeyboard_isKeyPressed(sfKeyNum3) && timer > 0.8f)
		{
			fichier = fopen("MAP3.bin", "r");
			fread(map, sizeof(char), 15000, fichier);
			fclose(fichier);
		}

		// Si la touche 4 est pressée alors on charge la 4
		if (sfKeyboard_isKeyPressed(sfKeyNum4) && timer > 0.8f)
		{
			fichier = fopen("MAPbonus.bin", "r");
			fread(map, sizeof(char), 12000, fichier);
			fclose(fichier);
		}


	}

	timer_c += GetDeltaTime();
	timer_c2 += GetDeltaTime();

	if (iModeDeJeu == 0)
	{
		if (sfKeyboard_isKeyPressed(sfKeyE) && timer > 0.3f)
		{
			for (int i = 0; i < 3; i++)
			{
				if (CalculD(ch[i].chestpos, CRayon) && ch[i].ChestState==0)
				{
					sfSound_play(coffre2);
					ch[i].ChestState = 1;
					blocage = 1;
					numerochest = i;
					timer_c2 = 0;
					coffstat++;
					nmcle++;
				}
			}
		}
	}
	if (blocage ==1)
	{ 
		couv(1);
		if (timer_c >= 3.4f)
		{
			timer_c = 0;
			if (ch[numerochest].chestrect.left == 64)
			{
				blocage = 2;
			}
			ch[numerochest].chestrect.left += 32;
			sfSprite_setTextureRect(ch[numerochest].chest, ch[numerochest].chestrect);
		}
	}
	if (blocage == 2)
	{
		if (timer_c >= 0.8f)
		{
			if (timer_c2>=11.f)
			{
				blocage = 0;
				couv(0);
				animpcoffre(0);
			}
			else
			{
				appararitionObjet();
				animpcoffre(4);
				
			}
		}
	}
	// 0 à 15 images pour l'animation de la porte || Fonction qui gère l'ouverture de la porte finale
	timeouverture += GetDeltaTime();
	if (nmcle == 4 && sfKeyboard_isKeyPressed(sfKeyE) && timeouverture > 0.15f && (CalculD(portedefinpos, 32)))
	{
		map[(int)portedefinpos.y / 32][(int)portedefinpos.x / 32] = 46;
		ouverture = sfTrue;	
		sfSprite_setPosition(porteanim, portedefinpos);
	
	}
	if (ouverture == sfTrue && timeouverture > 1.3f)
	{

		irectporte.left += 32;
		sfSprite_setTextureRect(porteanim, irectporte);
		isAnimated = sfTrue;
	 	timeouverture = 0.f;
	}
	if (irectporte.left == 32 * 16)
	{
		ouverture = sfFalse;

	}
}

float statcoffretime = 0.f;
int statueappartition = 0;

void appararitionObjet()
{
	// Selon le coffre ouvert on affiche l'orbe correspondante
	if (coffstat == ROUGE)
	{
		posorberouge.x = Pposition.x + 6.f;
		posorberouge.y = Pposition.y - 1.f;

		sfSprite_setPosition(orberouge, posorberouge);
		statueappartition = 3;
		statcoffretime = 0.f;
	}

	if (coffstat == VERTE)
	{
		posorbeverte.x = Pposition.x + 6.f;
		posorbeverte.y = Pposition.y - 1.f;

		sfSprite_setPosition(orbeverte, posorbeverte);
		statueappartition = 2;
		statcoffretime = 0.f;
		
	}

	if (coffstat == BLEU)
	{
		posorbebleu.x = Pposition.x + 6.f;
		posorbebleu.y = Pposition.y - 1.f;

		sfSprite_setPosition(orbebleu, posorbebleu);
		statueappartition = 1;
		statcoffretime = 0.f;
	
	}


}

float timemap = 0.f;
int changement = 0;
void changementMap(int _nb, int _tmp)
{
	
	changement += _tmp;
	if (changement>1) changement = 0;
	if (_nb == 23 && changement == 0 && nmcle == 1)
	{

		fichier = fopen("MAP1.bin", "r");
		fread(map, sizeof(char), 15000, fichier);
		fclose(fichier);
	}
	else if ((_nb == 23 || _nb == 20) && changement == 1 && nmcle >= 1)
	{

		fichier = fopen("MAPBonus.bin", "r");
		fread(map, sizeof(char), 12000, fichier);
		fclose(fichier);
	}
	else if (_nb == 23 && changement == 0 && nmcle == 2)
	{

		fichier = fopen("MAP2.bin", "r");
		fread(map, sizeof(char), 15000, fichier);
		fclose(fichier);
	}
	else if (_nb == 20 && changement == 0 && nmcle == 3 || nmcle == 4)
	{

		fichier = fopen("MAP3.bin", "r");
		fread(map, sizeof(char), 15000, fichier);
		fclose(fichier);
	}
	else
	{
		if (changement == 1) changement = 0;
		else  changement = 1;
	}
}


	



void displayMap(sfRenderWindow* _window, sfView* _cam)
{
	// Affichage du fond d'écran
	
	sfRenderWindow_drawSprite(_window, background1, NULL);


	// Initatisation des variables
	sfVector2i mousePosition;
	sfVector2i pixelPos = sfMouse_getPositionRenderWindow(_window);
	sfVector2f worldPos = sfRenderWindow_mapPixelToCoords(_window, pixelPos, cam);
	mousePosition = sfMouse_getPosition(_window);
	

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
				
				position.x = x * 32;
				position.y = y * 32;
				ch[NChest].chestpos.x = position.x;
				ch[NChest].chestpos.y = position.y;
				sfSprite_setPosition(ch[NChest].chest, position);
				sfSprite_setTextureRect(ch[NChest].chest, ch[NChest].chestrect);
				sfRenderWindow_drawSprite(_window, ch[NChest].chest, NULL);
				if (NChest == 2)
				{
					NChest = 0;
				}
				else
				{
					NChest++;
				}
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
			case 16:
				tileRect.left = 32 * 17;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 17 :
				tileRect.left = 32 * 18;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;	
			case 18:
				tileRect.left = 32 * 19;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 19:
				tileRect.left = 32 * 20;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 20:
				tileRect.left = 32 * 21;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 21:
				tileRect.left = 32 * 22;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 22:
				tileRect.left = 32 * 23;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 23:
				tileRect.left = 32 * 24;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 24:
				tileRect.left = 32 * 25;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 25:
				tileRect.left = 32 * 26;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 26:
				tileRect.left = 32 * 27;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 27:
				tileRect.left = 32 * 28;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 28:
				tileRect.left = 32 * 29;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 29:
				tileRect.left = 32 * 30;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 30:
				tileRect.left = 32 * 31;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 31:
				tileRect.left = 32 * 32;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case  32:
				tileRect.left = 32 * 33;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 33:
				tileRect.left = 32 * 34;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 34:
				tileRect.left = 32 * 35;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 35:
				tileRect.left = 32 * 36;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 36:
				tileRect.left = 32 * 37;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 37:
				tileRect.left = 32 * 38;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 38:
				tileRect.left = 32 * 39;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 39:
				tileRect.left = 32 * 40;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 40:
				tileRect.left = 32 * 41;
				position.x = x * 32;
				position.y = y * 32;
				portedefinpos.x = position.x;
				portedefinpos.y = position.y;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 41:
				tileRect.left = 32 * 42;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 42:
				tileRect.left = 32 * 43;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 43:
				tileRect.left = 32 * 44;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 44:
				tileRect.left = 32 * 45;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite, tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 45:
				tileRect.left = 32 * 46;
				position.x = x * 32;
				position.y = y * 32;
				sfSprite_setPosition(tileSprite, position);
				sfSprite_setTextureRect(tileSprite,tileRect);
				sfRenderWindow_drawSprite(_window, tileSprite, NULL);
				break;
			case 46:
				tileRect.left = 32 * 47;
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
		case 16 :
			tileRect.left = 32 * 17;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 17:
			tileRect.left = 32 * 18;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 18:
			tileRect.left = 32 * 19;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 19:
			tileRect.left = 32 * 20;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 20:
			tileRect.left = 32 * 21;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 21:	
			tileRect.left = 32 * 22;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
			case 22:
			tileRect.left = 32 * 23;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 23:
			tileRect.left = 32 * 24;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 24:
			tileRect.left = 32 * 25;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 25:
			tileRect.left = 32 * 26;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 26:
			tileRect.left = 32 * 27;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;	
		case 27:
			tileRect.left = 32 * 28;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 28:
			tileRect.left = 32 * 29;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 29:
			tileRect.left = 32 * 30;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case  30:
			tileRect.left = 32 * 31;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 31:
			tileRect.left = 32 * 32;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 32:
			tileRect.left = 32 * 33;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 33:
			tileRect.left = 32 * 34;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 34:
			tileRect.left = 32 * 35;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 35:
			tileRect.left = 32 * 36;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 36:
			tileRect.left = 32 * 37;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 37:
			tileRect.left = 32 * 38;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 38:
			tileRect.left = 32 * 39;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite,tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 39:
			tileRect.left = 32 * 40;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 40:
			tileRect.left = 32 * 41;
			position.x = worldPos.x;
			position.y = worldPos.y;
			portedefinpos.x = position.x;
			portedefinpos.y = position.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 41:
			tileRect.left = 32 * 42;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 42:
			tileRect.left = 32 * 43;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 43:
			tileRect.left = 32 * 44;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 44:
			tileRect.left = 32 * 45;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 45:
			tileRect.left = 32 * 46;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		case 46:
			tileRect.left = 32 * 47;
			position.x = worldPos.x;
			position.y = worldPos.y;
			sfSprite_setPosition(tileSprite, position);
			sfSprite_setTextureRect(tileSprite, tileRect);
			sfRenderWindow_drawSprite(_window, tileSprite, NULL);
			break;
		}
	}

	if (statueappartition == 1)
	{ // Si le coffre ouvert est le bleu alors on affiche l'orbe bleu
		statcoffretime += GetDeltaTime();
		if (statcoffretime < 0.01f)
		{
			sfRenderWindow_drawSprite(_window, orbebleu, NULL);
					
		}
		
	}
	if (statueappartition == 2)
	{ // Si le coffre ouvert est le vert alors on affiche l'orbe verte
		statcoffretime += GetDeltaTime();
		if (statcoffretime < 0.01f)
		{
			sfRenderWindow_drawSprite(_window, orbeverte, NULL);
			
		}
		
	}
	if (statueappartition == 3)
	{ // Si le coffre ouvert est le rouge alors on affiche l'orbe rouge
		statcoffretime += GetDeltaTime();
		if (statcoffretime < 0.01f)
		{
			sfRenderWindow_drawSprite(_window, orberouge, NULL);
			
		}
		
		
	}

	if (isAnimated == sfTrue)
	{
		sfRenderWindow_drawSprite(_window, porteanim, NULL);
	}

}

int onestsurquelcase(sfFloatRect _sprite)
{
	// Fonction qui renvoie le type de la case sur laquelle le personnage se trouve
	sfVector2i fretpos;

	fretpos.y = (_sprite.top + _sprite.height) / 32;
	fretpos.x = ((_sprite.left + _sprite.left + _sprite.width) / 2) / 32;
	
		if (map[fretpos.y][fretpos.x] == 0)
		{
			return 0;
		}
		if (map[fretpos.y][fretpos.x] == 1)
		{
			return 1;
		}
		if (map[fretpos.y][fretpos.x] == 6 || map[fretpos.y][fretpos.x] == 12 ||  map[fretpos.y][fretpos.x] == 13 ||  map[fretpos.y][fretpos.x] == 14 | map[fretpos.y][fretpos.x] == 15)
		{
			return 2;
		}
		if (map[fretpos.y][fretpos.x] == 16 || map[fretpos.y][fretpos.x] == 17 ||  map[fretpos.y][fretpos.x] == 18 ||  map[fretpos.y][fretpos.x] == 19)
		{
			return 3;
		}
		if (map[fretpos.y][fretpos.x] == 1)
		{
			return 4;
		}
		if (map[fretpos.y][fretpos.x] == 23)
		{
			return 23;
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
			fpos.y = (_sprite.top + 8 + _vitesse.y * GetDeltaTime()) / 32;
			fpos.x = (_sprite.left + _vitesse.x * GetDeltaTime()) / 32;
			fpos2.y = (_sprite.top + 8 + _vitesse.y * GetDeltaTime()) / 32;
			fpos2.x = (_sprite.width + _sprite.left + _vitesse.x * GetDeltaTime()) / 32;
			
			// Si la case est 5 4 3 9 alors, on renvoie vrai
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

			fpos.y = (_sprite.top + 10 + _vitesse.y * GetDeltaTime()) / 32;
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
			fpos2.y = (_sprite.top +10 + _vitesse.y * GetDeltaTime()) / 32;
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


void Position_joueur()
{
	int spawn_or_not = 0;
	// Fonction qui permet de récupérer la position du joueur sur la map

	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			if (map[y][x] == 9)
			{
				spawn_or_not++;
				Pposition.x = x*32 +9;
				Pposition.y = y*32 +6;
			}
		}
	}
	if (spawn_or_not == 0)
	{
		Pposition.x = actualposJ.x;
		Pposition.y = actualposJ.y;
	}
	
}


void Position_NPC()
{ // Fonction qui permet de récupérer la position du NPC sur la map
	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			if (map[y][x] == 7)
			{
				NPCpos.x = x * 32 +9;
				NPCpos.y = y * 32 +6;
				sfText_setPosition(Text, vector2f(NPCpos.x + 8.0f, NPCpos.y - 25.0f));
				sfRectangleShape_setPosition(rectangle, vector2f(NPCpos.x + 8.0f, NPCpos.y - 30.0f));
			}
		}
	}
	


}