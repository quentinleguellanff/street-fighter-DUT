#ifndef GREG_H
#define GREG_H
#include <Personnage.h>


class Greg : public Personnage
{
    public:
        Greg();
        Greg(int,sf::RectangleShape&);
        virtual ~Greg();
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
#endif // GREG_H
