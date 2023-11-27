#include "fin.h"
#include "SFML/Graphics.h"

sfVector2f ecrantitrepos = { 400.f,300.f };

sfVector2f ecrantitrescale = { 1.f,1.f };

sfView* camfin;
sfVector2f camfinrect = { 800.f ,600.f };


void initFin()
{
    camfin = sfView_create();

    sfView_setSize(camfin, camfinrect);

    ecrantitre = sfSprite_create();

    ecrantitreT = sfTexture_createFromFile("../Ressources/Textures/ecranfin.png", NULL);

    sfSprite_setTexture(ecrantitre, ecrantitreT, sfTrue);

    sfSprite_setOrigin(ecrantitre, vector2f(sfSprite_getGlobalBounds(ecrantitre).width / 2, sfSprite_getGlobalBounds(ecrantitre).height / 2));

    sfSprite_setPosition(ecrantitre, ecrantitrepos);

    sfSprite_setScale(ecrantitre, ecrantitrescale);

    sfView_setCenter(camfin, vector2f(400.f, 300.f));
}

void displayFin(sfRenderWindow* _window)
{
    sfRenderWindow_setView(_window, camfin);
    sfRenderWindow_drawSprite(_window, ecrantitre, NULL);
}