#include "fin.h"

void initFin()
{
	
	ecrantitreT = sfTexture_createFromFile("../Ressources/Textures/ecranfin.png", NULL);

	ecrantitre = sfSprite_create();

	sfSprite_setTexture(ecrantitre, ecrantitreT, sfTrue);

	sfSprite_setPosition(ecrantitre, vector2f(400, 300));


}

void displayFin(sfRenderWindow* _window)
{
	sfRenderWindow_clear(_window, sfBlack);

	sfRenderWindow_drawSprite(_window, ecrantitre, NULL);

	sfRenderWindow_display(_window);
}