#include "musique.h"
#include "tools.h"

// Initialisation des variables et define pour les chemins

#define MUSIQUE_PATH "../Ressources/Musics/"
#define SOUND_PATH "../Ressources/SoundsFX/"


void initMusique()
{	
	// Initialisation des musiques et des sons
	volume = 100;
	porte = sfMusic_createFromFile(MUSIQUE_PATH"ouvertureporte.ogg");
	menu = sfMusic_createFromFile(MUSIQUE_PATH"musiquemenu.ogg");
	editeur = sfMusic_createFromFile(MUSIQUE_PATH"musiqueediteur.ogg");

	forest = sfMusic_createFromFile(MUSIQUE_PATH"forest.ogg");

	coffre2 = sfSound_create();
	menu2 = sfSound_create(); 
	pas = sfSound_create(); 
	placement = sfSound_create();
	princesse = sfSound_create();
	paspierre = sfSound_create();
	pasdalle = sfSound_create();
	pasplanche = sfSound_create();
	pasterre = sfSound_create();
	passable = sfSound_create();
	



	coffrebuf = sfSoundBuffer_createFromFile(SOUND_PATH"coffreouverture.ogg");
	menubuf = sfSoundBuffer_createFromFile(SOUND_PATH"menu_selection.ogg");
	pasbuf = sfSoundBuffer_createFromFile(SOUND_PATH"pas.ogg");
	placementbuf = sfSoundBuffer_createFromFile(SOUND_PATH"placement.ogg");
	princessebuf = sfSoundBuffer_createFromFile(SOUND_PATH"princesseparle.ogg");
	paspierrebuf = sfSoundBuffer_createFromFile(SOUND_PATH"paspierre.ogg");
	pasdallebuf = sfSoundBuffer_createFromFile(SOUND_PATH"pasdalle.ogg");
	pasplanchebuf = sfSoundBuffer_createFromFile(SOUND_PATH"pasplanche.ogg");
	passablebuf = sfSoundBuffer_createFromFile(SOUND_PATH"passable.ogg");
	pasterrebuf = sfSoundBuffer_createFromFile(SOUND_PATH"pasterre.ogg");

	sfSound_setBuffer(coffre2, coffrebuf);
	sfSound_setBuffer(menu2, menubuf);
	sfSound_setBuffer(pas, pasbuf);
	sfSound_setBuffer(placement, placementbuf);
	sfSound_setBuffer(princesse, princessebuf);
	sfSound_setBuffer(paspierre, paspierrebuf);
	sfSound_setBuffer(pasdalle, pasdallebuf);
	sfSound_setBuffer(pasplanche, pasplanchebuf);
	sfSound_setBuffer(passable, passablebuf);
	sfSound_setBuffer(pasterre, pasterrebuf);

	sfMusic_setLoop(porte, sfFalse);
	sfMusic_setLoop(menu, sfTrue);
	sfMusic_setLoop(editeur, sfTrue);
	sfMusic_setLoop(forest, sfTrue);


	sfSound_setLoop(coffre2, sfFalse);
	sfSound_setLoop(menu2, sfFalse);
	sfSound_setLoop(pas, sfFalse);
	sfSound_setLoop(placement, sfFalse);
	sfSound_setLoop(princesse, sfFalse);
	sfSound_setLoop(paspierre, sfFalse);
	sfSound_setLoop(pasdalle, sfFalse);


	sfMusic_setVolume(porte, volume);
	sfMusic_setVolume(menu, volume);
	sfMusic_setVolume(editeur, volume);
	
	sfMusic_setVolume(forest, volume);


	sfSound_setVolume(coffre2, volume);
	sfSound_setVolume(menu2, volume);
	sfSound_setVolume(pas, volume);
	sfSound_setVolume(placement, volume);
	sfSound_setVolume(princesse, volume);
	sfSound_setVolume(paspierre, volume);
	sfSound_setVolume(pasdalle, volume);
	sfSound_setVolume(pasplanche, volume);
	sfSound_setVolume(passable, volume);
	sfSound_setVolume(pasterre, volume);

	
}


void updateMusique()
{ // Update des musiques et des sons pour la musique et les sons
	sfMusic_setVolume(porte, volume);
	sfMusic_setVolume(menu, 1);
	sfMusic_setVolume(editeur, volume);
	sfMusic_setVolume(forest, volume);

	sfSound_setVolume(coffre2, volume);
	sfSound_setVolume(menu2, volume);
	sfSound_setVolume(pas, volume);
	sfSound_setVolume(placement, volume);
	sfSound_setVolume(princesse, volume);
	sfSound_setVolume(paspierre, volume);
	sfSound_setVolume(pasdalle, volume);
	sfSound_setVolume(pasplanche, volume);
	sfSound_setVolume(passable, volume);
	sfSound_setVolume(pasterre, volume);

}