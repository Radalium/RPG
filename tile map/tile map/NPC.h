#include "tools.h"
#include "map.h"
#include <SFML/Graphics.h>


// Permet d'avoir ces variables en global pour les utiliser ailleur
sfVector2f NPCpos;
sfText* Text;
sfRectangleShape* rectangle;

void initNPC();

void updateNPC();

void DisplayNPC(sfRenderWindow* _window);

