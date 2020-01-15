#ifndef KEN_H
#define KEN_H

#include <Personnage.h>


class Ken : public Personnage
{
    public:
        Ken();
        Ken(int,sf::RectangleShape&);
        virtual ~Ken();
        void debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void reculer(sf::RenderWindow& window) override;
        bool coupDePoing(sf::RectangleShape,bool&,sf::RenderWindow&) override;
        void prendCoup(bool&,sf::RenderWindow&) override;
        bool sauter(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterAvancer(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterArriere(sf::RenderWindow&,sf::RectangleShape) override;
        void seBaisser(sf::RenderWindow&,sf::RectangleShape) override;

    protected:

    private:
};

#endif // KEN_H
