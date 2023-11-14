#include "tools.h"

sfTime sftime;
sfClock* sfclock;



void initTools()
{
	// Creation de l'horloge interne pour le temps
	sfclock = sfClock_create();
	srand(time(NULL));
}

float GetDeltaTime()
{
	// R�cupuration du temps en secondes
	return sfTime_asSeconds(sftime);
}

sfVector2f vector2f(float _x, float _y)
{
	// Cr�taion d'un sfvector2f de maniere plus simple
	sfVector2f tmp = { _x, _y };
	return tmp;
}


void restartClock()
{
	//	Red�marrage de l'horloge (remise a 0)
	sftime = sfClock_restart(sfclock);
}
