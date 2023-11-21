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
sfVector2f NPCpos = { 320.0f, 120.0f };
int parle = 0;
float rayonNPC;
float NPCtimer = 0.f;
sfFont* Font;
sfText* Text;
sfRectangleShape* rectangle;
float thickness = 1.0f;
char* clear = "";
char* un = "          Link,     \n       te voila !";
char* deux = "     J'ai besoin   \n    de ton aide !  ";
char* trois = "   Un grand mal \nest venu s'installer";
char* quatre = "    Tu te dois de \n    retrouver les\nmorceaux de l'orbe ";
char* cinq = "    Elle seule te \npermettra d'ouvrir\n  la porte divine";
char* six = "    Pour trouver\n  l'excalibur qui\n  pourra trancher\n         le mal !";
char* unun = "          Link,     \n     depeche toi !";
char* deuxdeux = " Arrete de me\n        gaver";
char* temple1 = "      Dirige toi\n      vers l'EST";
int deroulement = 2;
int spam = 0;
int blocage2 = 0;

void initNPC()
{
	// Initialisation du NPC
	NPCTexture = sfTexture_createFromFile(TEXTURE_PATH"princesse.png", NULL);
	NPC = sfSprite_create();
	sfSprite_setTexture(NPC, NPCTexture, sfTrue);
	sfSprite_setScale(NPC, NPCscale);
	sfSprite_setTextureRect(NPC, NPCrect);

	Font = sfFont_createFromFile("..\\Ressources\\Fonts\\FinkHeavy.ttf");
	Text = sfText_create();

	sfText_setFont(Text, Font);

	sfText_setColor(Text, sfBlack);
	sfText_setPosition(Text, vector2f(NPCpos.x + 8.0f, NPCpos.y- 25.0f));
	sfText_setScale(Text, vector2f(0.2f, 0.2f));

	rectangle = sfRectangleShape_create();
	sfRectangleShape_setFillColor(rectangle, sfWhite);
	sfRectangleShape_setPosition(rectangle, vector2f(NPCpos.x+8.0f, NPCpos.y-30.0f));
	sfRectangleShape_setSize(rectangle, vector2f(50.0f, 30.0f));
	sfRectangleShape_setOutlineThickness(rectangle,thickness);
	sfRectangleShape_setOutlineColor(rectangle, sfBlack);
}


void updateNPC()
{

	// Update du NPC
	sfFloatRect playerfrect = sfSprite_getGlobalBounds(NPC);
	rayonNPC = playerfrect.width ;

	//isTalking = sfFalse;
	if (sfKeyboard_isKeyPressed(sfKeyV) && CalculD(NPCpos, rayonNPC))
	{
		// elle parle

		isTalking = sfTrue;
		//coov(1);

	}

		if (isTalking== sfTrue) 
		{
			NPCtimer += GetDeltaTime();
			if(blocage2==0)sfText_setString(Text, un);
			if (NPCtimer > 5.f && spam==0)
			{
				switch (deroulement)
				{
				case 2:
					sfText_setString(Text, deux);
					deroulement += 1;
					NPCtimer = -0;
					blocage2 = 1;
					break;
				case 3:
					sfText_setString(Text, trois);
					deroulement += 1;
					NPCtimer = -0;
					break;
				case 4:
					sfText_setString(Text, quatre);
					deroulement += 1;
					NPCtimer = -0;
					break;
				case 5:
					sfText_setString(Text, cinq);
					deroulement += 1;
					NPCtimer = -0;
					break;
				case 6:
					sfText_setString(Text, six);
					deroulement += 1;
					NPCtimer = 0;
					break;
				case 7:
					sfText_setString(Text, unun);
					isTalking = sfFalse;
					NPCtimer = 0;
					deroulement = 0;
					spam = 1;
					//coov(2);
					break;
				}
			}
			if (NPCtimer > 5.f && spam == 1)
			{
				sfText_setString(Text, unun);

					isTalking = sfFalse;
					spam = 2;
					NPCtimer = 0;
					sfText_setString(Text, temple1);


			}
			if (NPCtimer > 5.f && spam == 2)
			{

					isTalking = sfFalse;
					NPCtimer = 0;


			}

				NPCanimTime += GetDeltaTime();
			

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
	if (isTalking)
	{
		sfRenderWindow_drawRectangleShape(_window, rectangle, NULL);
		sfRenderWindow_drawText(_window, Text, NULL);
	}
	
}

