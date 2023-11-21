#pragma once
#include "tools.h"


sfMusic* porte;
sfMusic* menu;
sfMusic* editeur;
sfMusic* pasplanche;
sfMusic* passable;
sfMusic* pasterre;
sfMusic* forest;

sfSound* coffre2;
sfSound* menu2;
sfSound* pas;
sfSound* placement;
sfSound* princesse;
sfSound* paspierre;
sfSound* pasdalle;

sfSoundBuffer* coffrebuf;
sfSoundBuffer* menubuf;
sfSoundBuffer* pasbuf;
sfSoundBuffer* placementbuf;
sfSoundBuffer* princessebuf;
sfSoundBuffer* paspierrebuf;
sfSoundBuffer* pasdallebuf;

int volume;

void initMusique();

void updateMusique();