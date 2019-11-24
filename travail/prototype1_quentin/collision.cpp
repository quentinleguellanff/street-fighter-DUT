#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

bool collision(sf::RectangleShape hurtbox,sf::RectangleShape hitbox){
    if((hurtbox.getPosition().x >= hitbox.getPosition().x) && ((hurtbox.getPosition().x+hurtbox.getSize().x) >= (hitbox.getPosition().x + hitbox.getSize().x))){
        cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
        return true;
    }
    else{
            cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
        return false;
    }



}
