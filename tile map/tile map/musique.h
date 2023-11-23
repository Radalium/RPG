#pragma once
#include "tools.h"


sfMusic* porte;
sfMusic* menu;
sfMusic* editeur;
sfMusic* forest;
sfMusic* grotte;
sfMusic* finson;

sfSound* coffre2;
sfSound* menu2;
sfSound* pas;
sfSound* placement;
sfSound* princesse;
sfSound* paspierre;
sfSound* pasplanche;
sfSound* passable;
sfSound* pasterre;


sfSoundBuffer* coffrebuf;
sfSoundBuffer* menubuf;
sfSoundBuffer* pasbuf;
sfSoundBuffer* placementbuf;
sfSoundBuffer* princessebuf;
sfSoundBuffer* paspierrebuf;
sfSoundBuffer* pasplanchebuf;
sfSoundBuffer* passablebuf;
sfSoundBuffer* pasterrebuf;

int volume;

void initMusique();

void updateMusique();