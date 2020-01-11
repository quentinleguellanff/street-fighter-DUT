#include "GestionFenetre.h"
//#include "Player.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
	GestionFenetre fenetre;

	while(fenetre.returnWindow().isOpen())
	{
		fenetre.action();
	}
	return 0;
}

