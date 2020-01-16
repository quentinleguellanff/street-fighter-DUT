#include "GestionFenetre.h"

using namespace std;

GestionFenetre::GestionFenetre()
{

	window.create(sf::VideoMode(1920,1080),"la Bagarre",sf::Style::Fullscreen);
	window.setFramerateLimit(120);
	window.setMouseCursorVisible(0);

    scene=Scene(window);
    selecEcran=0;

    menuPrinc= new MenuPrincipal(window.getSize().x,window.getSize().y);
    menuSel= new MenuSelection(window);
    menuCommandes= new MenuCommandes(window);
	menuBackground= new MenuBackground(window);

	if(!readyF.loadFromFile("background/SdHUDAtlas.png")) {
        std::cout<<"erreur background/SdHUDAtlas.png";
    }

    joueur1= new Player(1,window);
    joueur2= new Player(2,window);

    selecChamp_P1=-1;
    selecChamp_P2=-1;

    for(int i=0;i<=6;i++)
    {
    	_tabActionCombat.push_back(false);
    }

    readyFight.scale(2,2);

    if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
        std::cout<<"erreur musique";
    }
    //musique.setVolume(1.f) ;
    musique.play();
    musique.setLoop(true);
}

sf::RenderWindow& GestionFenetre::getWindow()
{

	return window;
}

void GestionFenetre::action()
{
	window.clear();
	sf::Event event;

	switch(selecEcran)	//menu principal
	{
	case -1:
		window.close();
		break;
    case 0:
       gestionMenuPrinc(event);
       break;
    case 1:
    	gestionSelecPerso(event);
    	break;
    case 2:
    	combat(event);
    	break;
    case 3:
    	gestionMenuCommande(event);
    	break;
    case 4:
    	gestionSelecScene(event);
    	break;
    }
}

void GestionFenetre::gestionMenuPrinc(sf::Event& event)
{
	while (window.pollEvent(event))
        menuPrinc->bouger(selecEcran,event,window);

    menuPrinc->draw(window);
    window.display();

    if(selecEcran==1)
    {
    	if (!musique.openFromFile("musique/theme_menu_perso.ogg")){
            std::cout<<"erreur musique";
        }
        musique.play();
        musique.setLoop(true);

        menuSel->resetClock();
    }
}

void GestionFenetre::gestionSelecPerso(sf::Event& event)
{
	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
            menuSel->bouger(event,window);
            selecEcran = menuSel->validationPerso(event,selecChamp_P1,selecChamp_P2);
    }

    window.clear();
    menuSel->draw(window);
    window.display();

    if(selecEcran==0)
    {
    	if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
            std::cout<<"erreur musique";
        }
        musique.play();
        musique.setLoop(true);

    }
}

void GestionFenetre::gestionMenuCommande(sf::Event& event)
{
	while (window.pollEvent(event))
        menuCommandes->retourMenu(selecEcran,event);
    menuCommandes->draw(window);
    window.display();
}

void GestionFenetre::gestionSelecScene(sf::Event& event)
{
	while (window.pollEvent(event))
    {
        menuBackground->retourMenu2(selecEcran,event, *menuSel,window);
        menuBackground->bouger(event, window);
        menuBackground->selectionner(event, window, selecEcran, scene,musique);
    }

    if(selecEcran==2)
    {
        if(selecChamp_P1==0)
        {
            champion_P1=new Greg(-1,scene,window);
        }else if(selecChamp_P1==1)
        {
            champion_P1=new Dhalsim(-1,scene,window);
        }else if(selecChamp_P1==2)
        {
            champion_P1=new Ryu(-1,scene,window);
        }

        if(selecChamp_P2==0)
        {
            champion_P2= new Greg(1,scene,window);
        }else if(selecChamp_P2==1)
        {
            champion_P2=new Dhalsim(1,scene,window);
        }else if(selecChamp_P2==2)
        {
            champion_P2=new Ryu(1,scene,window);
        }

        if(selecChamp_P1!=-1 && selecChamp_P2!=-1)
        {
            joueur1->setChampion(champion_P1);
            joueur2->setChampion(champion_P2);
        }
    }


    menuBackground->draw(window);
    window.display();
}

void GestionFenetre::combat(sf::Event& event)
{
	/* Gestion de la fermeture de la fenetre */
	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        joueur1->peutAttaquerP1(event,window);
        joueur2->peutAttaquerP2(event,window);
    }

	/* lancement des animations de début de combat */
	if(!_tabActionCombat[0] || !_tabActionCombat[1])
	{
		///
		readyFight.setTexture(readyF);
        readyFight.setTextureRect(sf::IntRect(666,435,300,74));
        readyFight.setPosition(sf::Vector2f(window.getSize().x/2-readyFight.getGlobalBounds().width/2,scene.getBottom()*0.5));

		if(!_tabActionCombat[0])
			_tabActionCombat[0]=joueur1->lancerApparition();
		if(!_tabActionCombat[1])
			_tabActionCombat[1]=joueur2->lancerApparition();
        clockReadyFight.restart();

	}else if( (joueur1->getPV()<=0 || joueur2->getPV()<=0) && ( ( joueur1->getChampion()->auSol() && joueur2->getChampion()->auSol() ) || _tabActionCombat[4] ) )
    {
    	_tabActionCombat[4]=true;
    	if(_tabActionCombat[5]==false)
    		_tabActionCombat[5]=joueur1->finPartie();
    	if(_tabActionCombat[6]==false)
    		_tabActionCombat[6]=joueur2->finPartie();

    	if(_tabActionCombat[5]==true && _tabActionCombat[6]==true)
    	{
        	finCombat();
        }
    }else
	{
        readyFight.setTextureRect(sf::IntRect(0,401,373,107));
        readyFight.setPosition(sf::Vector2f(window.getSize().x/2-readyFight.getGlobalBounds().width/2,window.getSize().y*0.4));
        if(clockReadyFight.getElapsedTime().asSeconds() > 1) {
            readyFight.setTextureRect(sf::IntRect(0,2,0,0));

        }
		/* Récuperation des actions à effectuer */
		if(_tabActionCombat[2])
		{
			joueur1->recuperationCommandesP1(*joueur2);
		}else if(_tabActionCombat[2]==false)
		{
			joueur1->recuperationAttaquesP1();
		}


		if(_tabActionCombat[3])
		{
			joueur2->recuperationCommandesP2(*joueur1);
		}else if(_tabActionCombat[3]==false)
		{
			joueur2->recuperationAttaquesP2();
		}

		/* Lancement des animations Player 2*/
		_tabActionCombat[3]=joueur2->lancerActions(*joueur1);

		/* Lancement des animations Player 1*/
		_tabActionCombat[2]=joueur1->lancerActions(*joueur2);

	}

	/* Gestion de la fermeture de la fenetre */
	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    /* affichage des élements graphiques */
    affichageCombat();
}

void GestionFenetre::affichageCombat()
{
	window.draw(scene.getSprite());

    joueur1->afficherEnergie(window);
	joueur2->afficherEnergie(window);

    joueur1->affichageChampion(window);
    joueur2->affichageChampion(window);

    joueur1->afficherHitspark(window);
    joueur2->afficherHitspark(window);

    window.draw(readyFight);
    window.display();
}

void GestionFenetre::finCombat()
{
	for(int i=0;i<=6;i++)
    {
    	_tabActionCombat[i]=false;
    }
    _tabActionCombat[2]=true;_tabActionCombat[3]=true;

	selecEcran=0;
	joueur1->resetPV();
	joueur1->getChampion()->resetHitbox();
	joueur2->resetPV();
	joueur2->getChampion()->resetHitbox();
	menuSel->reset(window);

	if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
        std::cout<<"erreur musique";
    }
    musique.setVolume(50.f);
    musique.play();
    musique.setLoop(true);
}
