#include "../IncludeManager.h"

using namespace std;

Dhalsim::Dhalsim(int orientation,Scene& s,sf::RenderWindow& window)
{
    double largeurFenetre=window.getSize().x;
    _scale=4*(largeurFenetre/1920);

    _orientation=-orientation;

    _cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi=0;_cptPrendCoup=0;
    _vsaut = -40;

    if (!_texture.loadFromFile("sprites/sprite_dhalsim.png"))
    {
        std::cout<<"Erreur au chargement du sprite";
    }
    _sprite.setTexture(_texture);
    _sprite.scale(_orientation*_scale,_scale);

    _icone.setTexture(_texture);
    _icone.setTextureRect(sf::IntRect(990,6490,97,104));
    _icone.scale(largeurFenetre/1920,largeurFenetre/1920);

    _hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Green);
    _hurtbox.setOutlineThickness(4);

    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(4);

    _gardebox.setFillColor(sf::Color(255,255,255,0));
    _gardebox.setOutlineColor(sf::Color::Blue);
    _gardebox.setOutlineThickness(4);

    _spriteHitSpark.setColor(sf::Color(130,255,130,255));

    setScene(s);
}



bool Dhalsim::victoire()
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

    if(timeAnim>delai)
    {
        switch (_cptApparition)
        {
        case 0:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(24,5634,50,126);

            _hurtbox.setSize(sf::Vector2f(0,0));

            if (!_effetSonore.openFromFile("musique/Dhalsim/victoire.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(82,5634,50,126);
            break;
        case 2:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(140,5634,56,126);
            break;
        case 3:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(204,5634,60,126);
            break;
        case 4:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(272,5634,65,126);
            break;
        case 5:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(345,5634,63,126);
            break;
        case 6:
            _cptApparition++;
            _clockAnim.restart();
            setSprite(417,5634,64,126);
            break;
        }

        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);
    }

    if(_cptApparition==7 && timeAnim>2000)
    {
        _clockAnim.restart();
        _cptApparition=0;
        fini=true;
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::mort()
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=100,deplacementX=_scene.getRightLimit()/15;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

    if(timeAnim>delai)
    {
        switch (_cptApparition)
        {
        case 0:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(102,5112,90,111);
            _hurtbox.setSize(sf::Vector2f(0,0));
            _posX-=deplacementX*_orientation;

            if (!_effetSonore.openFromFile("musique/Dhalsim/mort.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(200,5112,93,111);
            _posX-=deplacementX*_orientation;
            break;
        case 2:
            _cptApparition++;
            _clockAnim.restart();
            setSprite(301,5112,130,111);
            _posX-=deplacementX*_orientation;
            break;
        case 3:
            _cptApparition++;
            _clockAnim.restart();
            setSprite(439,5112,127,111);
            break;
        case 4:
            _cptApparition++;
            _clockAnim.restart();
            setSprite(300,5328,141,39);
            break;

        }

        if(_cptApparition >=3)
            _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);

    }

    if(_cptApparition==5 && timeAnim>2000)
    {
        _clockAnim.restart();
        _cptApparition=0;
        fini=true;
    }


    keepInWalls();
    return fini;
}

bool Dhalsim::parade(int* degats,sf::Sprite& effet)
{
    bool fini=false;
    _cptSauter=0;
    _cptAction=0;
    effet.setTextureRect(sf::IntRect(0,0,0,0));
    _hurtbox.setSize(sf::Vector2f(0,0));

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;

    if(_cptPrendCoup==0)
    {
        setSprite(125,4747,63,100);
        _cptPrendCoup++;
    }
    else if(timeAnim > delai)
    {
        if(_cptPrendCoup==1)
        {
            _clockAnim.restart();
            _cptPrendCoup++;
        }
        else
        {
            _clockAnim.restart();
            _cptPrendCoup=0;
            fini=true;
            *degats=0;
        }
    }

    sf::Time elapsedDep = _clockMove.getElapsedTime();
    int timeDep = elapsedDep.asMilliseconds();
    int delaiDep=20,deplacement=_scene.getRightLimit()/200*_orientation;

    if(timeDep>delaiDep)
    {
        _clockMove.restart();
        _posX-=deplacement;
        _sprite.setPosition(_posX,_posY);
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::prendCoup(int* degats,sf::Sprite& effet,int& energie)
{
    *degats=-1;
    bool fini=false;
    _cptSauter=0;
    _cptAction=0;
    _vsaut=-40;
    effet.setTextureRect(sf::IntRect(0,0,0,0));
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    _hurtbox.setSize(sf::Vector2f(0,0));
    _gardebox.setSize(sf::Vector2f(0,0));

    if(timeAnim > delai)
    {
        switch(_cptPrendCoup)
        {
        case 0:
            _clockAnim.restart();
            _cptPrendCoup++;
            setSprite(24,4996,85,100);
            _posX-=10*_scale*_orientation;

            energie+=5;

            if (!_effetSonore.openFromFile("musique/Dhalsim/degat.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _clockAnim.restart();
            _cptPrendCoup++;
            setSprite(117,4996,90,100);
            _posX-=10*_scale*_orientation;
            break;
        case 2:
            _clockAnim.restart();
            _cptPrendCoup++;
            setSprite(215,4996,93,100);
            _posX-=10*_scale*_orientation;
            break;
        case 3:
            _clockAnim.restart();
            _cptPrendCoup++;
            setSprite(117,4996,90,100);
            break;
        case 4:
            _clockAnim.restart();
            _cptPrendCoup=0;
            setSprite(24,163,96,103);
            fini=true;
            *degats=0;
            break;
        }
    }

    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Dhalsim::apparition(sf::Sprite& bandeau)
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    bool fini=false;
    int delai=200;

    if(_cptApparition==0)
    {
        bandeau.setTexture(_texture);
        bandeau.setTextureRect(sf::IntRect(0,0,0,0));
        bandeau.setScale(_orientation*_scale,_scale);

        setSprite(24,32,51,115);
        _cptApparition ++;

        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);

        if (!_effetSonore.openFromFile("musique/Dhalsim/apparition.ogg"))
            std::cout<<"erreur musique";
        _effetSonore.play();
    }
    else if(timeAnim>delai)
    {
        switch(_cptApparition)
        {
        case 1:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(83,32,52,115);
            _posX-=1*_scale*_orientation;
            break;
        case 2:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(143,32,53,115);
            _posX-=1*_scale*_orientation;
            break;
        case 3:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(204,32,59,115);
            _posX-=6*_scale*_orientation;
            bandeau.setTextureRect(sf::IntRect(462, 70,78,77));
            bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);
            break;
        case 4:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(271,32,64,115);
            _posX-=5*_scale*_orientation;
            bandeau.setTextureRect(sf::IntRect(542, 70,78,77));
            break;
        case 5:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(343,32,58,115);
            _posX+=6*_scale*_orientation;
            bandeau.setTextureRect(sf::IntRect(622, 70,78,77));
            break;
        case 6:
            _cptApparition ++;
            _clockAnim.restart();
            setSprite(409,32,51,115);
            _posX+= 13*_scale*_orientation;

            bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);
            break;
        }
        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);
    }

    if(_cptApparition>=7)
    {
        _cptApparition++;
        bandeau.setPosition(_posX-((_tailleSprite.x+_cptApparition*3)*_orientation),_posY+_cptApparition);
    }
    if(_cptApparition==70)
    {
        bandeau.setTextureRect(sf::IntRect(0,0,0,0));
        _cptApparition=0;
        fini=true;
        _sprite.setPosition(_posX,_posY);
    }


    return fini;
}

void Dhalsim::statique(Personnage& champEnnemi)
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=150;

    if(timeAnim>delai)
    {
        switch (_cptStatic)
        {
        case 0:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(24,163,96,103);
            break;
        case 1:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(128,163,97,103);
            break;
        case 2:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(233,163,94,103);
            break;
        case 3:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(335,163,94,103);
            break;
        case 4:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(437,163,93,103);
            break;
        case 5:
            _cptStatic ++;
            _clockAnim.restart();
            setSprite(538,163,92,103);
            break;
        case 6:
            _cptStatic=0;
            _clockAnim.restart();
            setSprite(638,163,91,103);
            break;
        }
        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);
    }

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    _hitbox.setSize(sf::Vector2f(0,0));
    _gardebox.setSize(sf::Vector2f(0,0));


    rotate(champEnnemi);
    int n=0;
    collision(champEnnemi,n);
    keepInWalls();
}


void Dhalsim::garde()
{
    _cptStatic=0;

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=70;

    if(timeAnim>delaiAnim)
    {
        _clockAnim.restart();
        setSprite(125,4747,63,100);
        _gardebox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y));
        _gardebox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY);
    }

    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
}
void Dhalsim::avancer(Personnage& champEnnemi)
{
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    int deplacement=8;

    _posY=_scene.getBottom()-_tailleSprite.y;

    collision(champEnnemi,deplacement);

    if(timeMove>10)
    {
        _posX= _posX+deplacement*_orientation;
        _clockMove.restart();
    }

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;

    if(deplacement==0)
    {
        statique(champEnnemi);
    }
    else if(timeAnim>delai)
    {
        switch (_cptAvancer)
        {
        case 0:
            _sprite.setPosition(_posX,_posY);
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(24,284,75,101);

            break;
        case 1:
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(107,284,68,101);
            break;
        case 2:
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(183,284,61,101);
            break;
        case 3:
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(252,284,58,101);
            break;
        case 4:
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(318,284,67,101);
            break;
        case 5:
            _cptAvancer ++;
            _clockAnim.restart();
            setSprite(393,284,67,101);
            break;
        case 6:
            _cptAvancer++;
            _clockAnim.restart();
            setSprite(468,284,63,101);
            break;
        case 7:
            _cptAvancer=0;
            _clockAnim.restart();
            setSprite(539,284,66,101);
            break;
        }
    }
    collision(champEnnemi,deplacement);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y));
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
    rotate(champEnnemi);
    keepInWalls();
}


void Dhalsim::reculer()
{
    _cptStatic=0;

    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    int deplacement=6;

    _posY=_scene.getBottom()-_tailleSprite.y;

    if(timeMove>10)
    {
        _posX= _posX-deplacement*_orientation;
        _clockMove.restart();
    }

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;

    if(timeAnim > delai)
    {
        switch (_cptReculer)
        {
        case 0:
            _sprite.setPosition(_posX,_posY);
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(614,282,69,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 1:
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(691,282,63,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 2:
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(762,282,60,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 3:
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(830,282,63,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 4:
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(901,282,62,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 5:
            _cptReculer ++;
            _clockAnim.restart();
            setSprite(971,282,57,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 6:
            _cptReculer++;
            _clockAnim.restart();
            setSprite(1036,282,60,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        case 7:
            _cptReculer=0;
            _clockAnim.restart();
            setSprite(1104,282,63,103);
            _posX-=_orientation*deplacement;
            _sprite.setPosition(_posX,_posY);
            break;
        }
    }
    _gardebox.setSize(sf::Vector2f(0,0));
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y));
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
    keepInWalls();
}


bool Dhalsim::sauter(int& lancerAttaque,Personnage& champEnnemi,int* degats,int& energie)
{
    _cptStatic=0;

    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    float v_grav = 1.7;

    if(timeMove > 10)
    {
        _vsaut += v_grav;
        _posY += _vsaut;
        _clockMove.restart();

        _sprite.setPosition(_posX,_posY);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    }

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;

    if(lancerAttaque!=-1)
    {
        bool enAttaque=false;

        if(lancerAttaque==1)
            enAttaque=sautPunch(champEnnemi,degats,energie);
        else if(lancerAttaque==2)
            enAttaque=sautKick(champEnnemi,degats,energie);

        if(enAttaque)
        {
            lancerAttaque=-1;
            if(_cptSauter<4)
                _cptSauter=7-_cptSauter;
        }

    }
    else
    {

        if(_cptSauter==0)
        {
            setSprite(974,1705,50,126);
            _clockAnim.restart();
            _cptSauter++;

            if (!_effetSonore.openFromFile("musique/Dhalsim/saut.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
        }
        else
        {
            int n=0;
            collisionsaut(champEnnemi,n);

            if(_cptSauter<8 && timeAnim>delai)
            {
                _cptSauter ++;
                _clockAnim.restart();
            }

            switch (_cptSauter)
            {
            case 1:
                setSprite(1084,1730,57,101);
                break;
            case 2:
                setSprite(1148,1744,60,87);
                break;
            case 7:
                setSprite(1084,1730,57,101);
                break;
            case 8:
                setSprite(974,1705,50,126);
                if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom())
                {
                    _cptSauter ++;
                }
                break;
            case 9:
                _cptSauter =0;
                setSprite(24,163,96,103);
                _posY=_scene.getBottom()-_tailleSprite.y;
                _vsaut = -40;
                fini = true;
                break;
            }
        }
    }

    keepInWalls();
    return fini;
}


bool Dhalsim::sauterAvant(Personnage& champEnnemi)
{
    _cptStatic=0;

    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    float v_grav = 1.7;
    int deplacementX=15;

    if(timeMove > 10)
    {
        _vsaut += v_grav;
        _posY += _vsaut;
        collisionsaut(champEnnemi,deplacementX);

        if(_cptSauter!=8)
            _posX += deplacementX*_orientation;

        _clockMove.restart();

        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    }

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=60;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch(_cptSauter)
        {
        case 0:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(108,1720,68,111);

            if (!_effetSonore.openFromFile("musique/Dhalsim/saut.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(108,1720,68,111);
            break;
        case 2:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(254,1756,68,75);
            break;
        case 3:
            _clockAnim.restart();
            _cptSauter++;
            break;
        case 4:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(418,1770,79,61);
            break;
        case 5:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(505,1770,57,61);
            break;
        case 6:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(570,1784,103,47);
            break;
        case 7:
            _clockAnim.restart();
            setSprite(108,1720,68,111);
            if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom())
            {
                _cptSauter ++;
                setSprite(24,1720,82,111);
            }
            break;
        case 8:
            _clockAnim.restart();
            _cptSauter=0;
            _vsaut=-40;
            fini=true;
            rotate(champEnnemi);
            break;
        }
    }

    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

bool Dhalsim::sauterArriere(Personnage& champEnnemi)
{
    _cptStatic=0;

    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    float v_grav = 1.7;
    int deplacementX=15;

    if(timeMove > 10)
    {
        _clockMove.restart();

        _vsaut += v_grav;
        _posY += _vsaut;
        collisionsaut(champEnnemi,deplacementX);

        if(_cptSauter!=8)
            _posX -= deplacementX*_orientation;

        _sprite.setPosition(_posX,_posY);

        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    }

    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch(_cptSauter)
        {
        case 0:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(108,1720,68,111);

            if (!_effetSonore.openFromFile("musique/Dhalsim/saut.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(108,1720,68,111);
            break;
        case 2:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(570,1784,103,47);
            break;
        case 3:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(505,1770,57,61);
            break;
        case 4:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(418,1770,79,61);
            break;
        case 5:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(330,1785,80,46);
            break;
        case 6:
            _clockAnim.restart();
            _cptSauter++;
            setSprite(254,1756,68,75);
            break;
        case 7:
            _clockAnim.restart();
            setSprite(108,1720,68,111);
            if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom())
            {
                _cptSauter ++;
                setSprite(24,1720,82,111);
            }
            break;
        case 8:
            _clockAnim.restart();
            _cptSauter=0;
            _vsaut=-40;
            fini=true;
            break;
        }
    }

    keepInWalls();
    return fini;
}

void Dhalsim::accroupi(bool garde)
{
    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=35;
    if(_cptAccroupi==0)
    {
        if(timeAnim>delai)
        {
            _clockAnim.restart();
            _cptAccroupi++;
            setSprite(24,1424,82,95);
            _posY=_scene.getBottom()-_tailleSprite.y;
            _sprite.setPosition(_posX,_posY);
            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
            _hurtbox.setPosition(_posX,_posY);
        }
    }
    else if(_cptAccroupi==1)
    {
        if(timeAnim>delai)
        {
            _clockAnim.restart();
            _cptAccroupi++;
            setSprite(114,1424,61,95);
            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.9));
            _hurtbox.setPosition(_posX+_tailleSprite.x*0.1,_posY+_tailleSprite.y*0.1);
        }
    }
    else
    {
        if(timeAnim>delai)
        {
            _clockAnim.restart();
            if(garde==true)
            {
                setSprite(263,4776,59,71);
            }
            else
                setSprite(183,1424,60,95);
        }
    }
}


bool Dhalsim::punch(Personnage& champEnnemi, int* degats,int& energie)
{
    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch (_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(24,419,82,117);

            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
            _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Dhalsim/coup_poing.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(114,419,74,117);
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(197,419,108,117);
            _hitbox.setSize(sf::Vector2f(40*_scale,20*_scale));
            _hitbox.setPosition(_posX+68*_scale*_orientation,_posY+56*_scale);
            _spriteHitSpark.setPosition(_posX+68*_scale*_orientation,_posY+56*_scale);
            break;
        case 3:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(313,419,108,117);
            break;
        case 4:
            _cptAction =0;
            _clockAnim.restart();
            setSprite(429,419,75,117);
            fini=true;
            _hitbox.setSize(sf::Vector2f(0,0));
            break;
        }
    }

    if(collisionCoup(champEnnemi))
    {
        if(_peutHitSpark)
            _hitSpark=true;
        *degats=5;
        energie+=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::sautPunch(Personnage& champEnnemi,int* degats,int& energie)
{
    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;

    if(timeAnim>delai)
    {
        switch(_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(896,1847,69,95);

            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
            _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Dhalsim/coup_poing.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(973,1847,58,95);
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(1039,1847,105,95);

            _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.5));
            _hitbox.setPosition(_posX+_tailleSprite.x*0.6*_orientation,_posY+_tailleSprite.y*0.2);
            break;
        case 3:
            _cptAction=0;
            _clockAnim.restart();
            setSprite(973,1847,58,95);
            fini=true;

            _hitbox.setSize(sf::Vector2f(0,0));
            break;
        }
    }

    if(collisionCoup(champEnnemi))
    {
        *degats=5;
        energie+=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::punchSP(sf::Sprite& inutile,Personnage& champEnnemi, int* degats,int& energie)
{
    if(energie<20)
    {
        energie=-100;
        return true;
    }

    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=30;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch (_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(24,660,86,92);

            _posX+=2*_scale*_orientation;

            if (!_effetSonore.openFromFile("musique/Dhalsim/punch_sp.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(118,665,95,87);
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(221,688,143,64);
            break;
        case 3:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(372,688,271,64);

            _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
            _hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.1);
            _spriteHitSpark.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.1);
            break;
        case 4:
            if(timeAnim>delai*4)
            {
                _cptAction++;
                _clockAnim.restart();
                setSprite(651,688,143,64);
                _hitbox.setSize(sf::Vector2f(0,0));
            }
            break;
        case 5:
            _cptAction++;
            _clockAnim.restart();
            setSprite(802,688,147,64);
            break;
        case 6:
            _cptAction++;
            _clockAnim.restart();
            setSprite(957,671,96,81);
            break;
        case 7:
            _cptAction++;
            _clockAnim.restart();
            setSprite(1061,665,95,87);
            break;
        case 8:
            _cptAction++;
            _clockAnim.restart();
            setSprite(1164,663,86,89);
            break;
        case 9:
            _cptAction++;
            _clockAnim.restart();
            setSprite(1258,660,84,92);
            break;
        case 10:
            _cptAction=0;
            _clockAnim.restart();
            setSprite(24,163,96,103);
            fini=true;
            energie-=25;
            _posX+=2*_scale*_orientation;
            break;
        }
        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);
    }

    if(collisionCoup(champEnnemi))
    {
        if(_peutHitSpark)
            _hitSpark=true;
        *degats=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    return fini;
}

bool Dhalsim::kick(Personnage& champEnnemi, int* degats,int& energie)
{
    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=55;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch (_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(24,768,77,113);

            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
            _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Dhalsim/coup_pied.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(109,768,56,113);
            _posX+= 18*_scale*_orientation;
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(173,768,126,113);
            _posX-=8*_scale*_orientation;

            _hitbox.setSize(sf::Vector2f(39*_scale,22*_scale));
            _hitbox.setPosition(_posX+87*_scale*_orientation,_posY+51*_scale);
            _spriteHitSpark.setPosition(_posX+87*_scale*_orientation,_posY+51*_scale);
            break;
        case 3:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(307,768,122,113);
            break;
        case 4:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(437,768,56,113);
            _posX+=8*_scale*_orientation;

            _hitbox.setSize(sf::Vector2f(0,0));
            break;
        case 5:
            _cptAction =0;
            _clockAnim.restart();
            setSprite(501,768,77,113);
            _posX-=18*_scale*_orientation;
            fini=true;
            break;
        }
        _sprite.setPosition(_posX,_posY);
    }

    if(collisionCoup(champEnnemi))
    {
        if(_peutHitSpark)
            _hitSpark=true;
        *degats=7;
        energie+=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::sautKick(Personnage& champEnnemi, int* degats,int& energie)
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=80,deplacement=_scene.getBottom()/6;
    bool fini=false;

    if(timeAnim>delai)
    {
        switch(_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(601,2319,53,110);

            _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
            _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Dhalsim/coup_pied.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(662,2319,63,110);
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(733,2319,99,110);

            _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
            _hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.25);
            _spriteHitSpark.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.25);
            break;
        case 3:
            _cptAction =0;
            _clockAnim.restart();
            setSprite(840,2319,70,110);
            fini=true;

            _hitbox.setSize(sf::Vector2f(0,0));
            break;
        }
    }

    if(collisionCoup(champEnnemi))
    {
        *degats=10;
        energie+=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    keepInWalls();
    return fini;
}

bool Dhalsim::kickSP(Personnage& champEnnemi, int* degats,int& energie)
{
    if(energie<20)
    {
        energie=-100;
        return true;
    }

    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;

    if(timeAnim > delai)
    {
        switch (_cptAction)
        {
        case 0:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(24,1165,77,113);

            _posX+=2*_scale*_orientation;

            if (!_effetSonore.openFromFile("musique/Dhalsim/punch_sp.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
            break;
        case 1:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(109,1159,97,119);
            break;
        case 2:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(214,1173,56,105);
            break;
        case 3:
            _cptAction ++;
            _clockAnim.restart();
            setSprite(278,1173,126,105);
            break;
        case 4:
            _cptAction++;
            _clockAnim.restart();
            setSprite(412,1173,232,105);

            _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.3));
            _hitbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
            break;
        case 5:
            if(timeAnim>delai*2)
            {
                _cptAction++;
                _clockAnim.restart();
                setSprite(652,1173,126,105);

                _hitbox.setSize(sf::Vector2f(0,0));
            }
            break;
        case 6:
            _cptAction++;
            _clockAnim.restart();
            setSprite(924,1173,56,105);
            break;
        case 7:
            _cptAction++;
            _clockAnim.restart();
            setSprite(988,1173,100,105);
            break;
        case 8:
            _cptAction=0;
            _clockAnim.restart();
            setSprite(24,163,96,103);
            fini=true;
            energie-=25;
            _posX+=2*_scale*_orientation;
            break;
        }
        _posY=_scene.getBottom()-_tailleSprite.y;
        _sprite.setPosition(_posX,_posY);
    }

    if(collisionCoup(champEnnemi))
    {
        if(_peutHitSpark)
            _hitSpark=true;
        *degats=10;

        if(champEnnemi.getPosX()==_scene.getRightLimit())
            _posX-=25*_scale*_orientation;
        else if(champEnnemi.getPosX()<=5)
            _posX+=25*_scale;
    }

    return fini;
}

bool Dhalsim::SP(sf::Sprite& bouleFeu,Personnage& champEnnemi, int* degats,int& energie)
{
    if(energie<50)
    {
        energie=-100;
        return true;
    }

    _cptStatic=0;
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;

    if(timeAnim > delai)
    {
	    switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(24,3233,76,120);
		    _posX-=10*_scale*_orientation;

		    if (!_effetSonore.openFromFile("musique/Dhalsim/yoga_fire.ogg"))
		        std::cout<<"erreur musique";
			_effetSonore.play();

		    bouleFeu.setTexture(_texture);
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(108,3233,81,120);
		    _posX-=6*_scale*_orientation;
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(197,3233,58,120);
		    _posX+=28*_scale*_orientation;
			break;
		case 3:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(263,3233,92,120);
		    _posX-=4*_scale*_orientation;

			bouleFeu.setTextureRect(sf::IntRect(357,3355,38,25));
			bouleFeu.setScale(_orientation*_scale,_scale);
			bouleFeu.setPosition(_posX+(_tailleSprite.x*_orientation/2),_posY+(_tailleSprite.y/3));
			break;
		}
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptAction>=4 && _cptAction<8)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(310,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>7 && _cptAction<11)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(263,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>10 && _cptAction<15)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(217,3355,38,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>14 && _cptAction<20)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(167,3355,42,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>19 && _cptAction<24)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(119,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>23 && _cptAction<28)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(71,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>27)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(24,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}

	if(_cptAction>4)
	{
		if( (_orientation==1 && bouleFeu.getPosition().x>=_scene.getRightLimit()) || (_orientation==-1 && bouleFeu.getPosition().x<=_scene.getLeftLimit()) )
		{
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			fini=true;
			energie-=50;
			_cptAction=0;
		}

		if(collisionCoup(champEnnemi))
		{
			*degats=30;

			if(champEnnemi.getPosX()==_scene.getRightLimit())
				_posX-=25*_scale*_orientation;

			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			fini=true;
			energie-=50;
			_cptAction=0;
		}
	}

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

    _hitbox.setSize(sf::Vector2f(bouleFeu.getGlobalBounds().width,bouleFeu.getGlobalBounds().height));
    _hitbox.setPosition(bouleFeu.getPosition().x,bouleFeu.getPosition().y);


    keepInWalls();
    return fini;
}
