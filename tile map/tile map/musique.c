#include "musique.h"
#include "tools.h"

#define MUSIQUE_PATH "../Ressources/Musics/"
#define SOUND_PATH "../Ressources/Sounds/"
int volume = 100;




void initMusique()
{
	porte = sfMusic_createFromFile(MUSIQUE_PATH"ouvertureporte.ogg");
	menu = sfMusic_createFromFile(MUSIQUE_PATH"musiquemenu.ogg");
	editeur = sfMusic_createFromFile(MUSIQUE_PATH"musiqueediteur.ogg");

	coffre = sfSound_createFromFile(SOUND_PATH"coffreouverture.ogg");
	menu2 = sfSound_createFromFile(SOUND_PATH"menuselection.ogg");
	pas = sfSound_createFromFile(SOUND_PATH"pas.ogg");
	placement = sfSound_createFromFile(SOUND_PATH"placement.ogg");
	princesse = sfSound_createFromFile(SOUND_PATH"princesseparle.ogg");

	sfMusic_setLoop(porte, sfFalse);
	sfMusic_setLoop(menu, sfTrue);
	sfMusic_setLoop(editeur, sfTrue);

	sfSound_setLoop(coffre, sfFalse);
	sfSound_setLoop(menu2, sfFalse);
	sfSound_setLoop(pas, sfFalse);
	sfSound_setLoop(placement, sfFalse);
	sfSound_setLoop(princesse, sfFalse);

	sfMusic_setVolume(porte, volume);
	sfMusic_setVolume(menu, volume);
	sfMusic_setVolume(editeur, volume);

	sfSound_setVolume(coffre, volume);
	sfSound_setVolume(menu2, volume);
	sfSound_setVolume(pas, volume);
	sfSound_setVolume(placement, volume);
	sfSound_setVolume(princesse, volume);
}

