#ifndef RYU_H
#define RYU_H

#include <Personnage.h>


class Ryu : public Personnage
{
    public:
        Ryu();
        Ryu(int);
        virtual ~Ryu();
        void debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;

    protected:

    private:
};

#endif // RYU_H
