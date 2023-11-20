#include "musique.h"
#include "tools.h"

#define MUSIQUE_PATH "../Ressources/Musics/"
#define SOUND_PATH "../Ressources/SoundsFX/"


void initMusique()
{
	volume = 100;
	porte = sfMusic_createFromFile(MUSIQUE_PATH"ouvertureporte.ogg");
	menu = sfMusic_createFromFile(MUSIQUE_PATH"musiquemenu.ogg");
	editeur = sfMusic_createFromFile(MUSIQUE_PATH"musiqueediteur.ogg");

	coffre2 = sfSound_create();
	menu2 = sfSound_create(); 
	pas = sfSound_create(); 
	placement = sfSound_create();
	princesse = sfSound_create();

	coffrebuf = sfSoundBuffer_createFromFile(SOUND_PATH"coffreouverture.ogg");
	menubuf = sfSoundBuffer_createFromFile(SOUND_PATH"menu_selection.ogg");
	pasbuf = sfSoundBuffer_createFromFile(SOUND_PATH"pas.ogg");
	placementbuf = sfSoundBuffer_createFromFile(SOUND_PATH"placement.ogg");
	princessebuf = sfSoundBuffer_createFromFile(SOUND_PATH"princesseparle.ogg");

	sfSound_setBuffer(coffre2, coffrebuf);
	sfSound_setBuffer(menu2, menubuf);
	sfSound_setBuffer(pas, pasbuf);
	sfSound_setBuffer(placement, placementbuf);
	sfSound_setBuffer(princesse, princessebuf);

	sfMusic_setLoop(porte, sfFalse);
	sfMusic_setLoop(menu, sfTrue);
	sfMusic_setLoop(editeur, sfTrue);

	sfSound_setLoop(coffre2, sfFalse);
	sfSound_setLoop(menu2, sfFalse);
	sfSound_setLoop(pas, sfFalse);
	sfSound_setLoop(placement, sfFalse);
	sfSound_setLoop(princesse, sfFalse);


	sfMusic_setVolume(porte, volume);
	sfMusic_setVolume(menu, volume);
	sfMusic_setVolume(editeur, volume);

	sfSound_setVolume(coffre2, volume);
	sfSound_setVolume(menu2, volume);
	sfSound_setVolume(pas, volume);
	sfSound_setVolume(placement, volume);
	sfSound_setVolume(princesse, volume);
}


void updateMusique()
{
	sfMusic_setVolume(porte, volume);
	sfMusic_setVolume(menu, volume);
	sfMusic_setVolume(editeur, volume);

	sfSound_setVolume(coffre2, volume);
	sfSound_setVolume(menu2, volume);
	sfSound_setVolume(pas, volume);
	sfSound_setVolume(placement, volume);
	sfSound_setVolume(princesse, volume);
}