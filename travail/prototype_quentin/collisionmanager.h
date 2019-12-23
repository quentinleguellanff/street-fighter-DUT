#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"


class collisionmanager
{
    private:
    public:
        collisionmanager();
        void collisionpersonnage(Joueur& joueur1, Joueur& joueur2);
        virtual ~collisionmanager();
};

#endif // COLLISIONMANAGER_H
