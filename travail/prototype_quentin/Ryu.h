#ifndef RYU_H
#define RYU_H

#include <Personnage.h>


class Ryu : public Personnage
{
    public:
        Ryu();
        Ryu(int,sf::RectangleShape&);
        virtual ~Ryu();
        void debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void reculer(sf::RenderWindow& window) override;
        bool coupDePoing(sf::RectangleShape,bool&,sf::RenderWindow&) override;
        void prendCoup(bool&,sf::RenderWindow&) override;
        bool sauter(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterAvancer(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterArriere(sf::RenderWindow&,sf::RectangleShape) override;

    protected:

    private:
};

#endif // RYU_H
