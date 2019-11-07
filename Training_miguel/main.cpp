#include "fonction.h"
#include "hitbox.h"
#include "personnage.h"
#include "background.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920,1080),"la Bagarre");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	Background background(window);

	Personnage perso(background);

	bool noMove=false, forward=false,backward=false, crouch=false, jump=false,jumpForward=false,jumpBackward=false,inAction=false, enMonte=true;
	bool punch=false,kick=false;
	int xNoMove=-1, xForward=-1,xBackward=-1, xCrouch=-1, xJump=-1,xJumpDirection=5,xPunch=-1,xKick=-1;
	sf::Clock clockAnim;
	int timeanim;

	float controller0_axisX, controller0_axisY;


	while(window.isOpen())
	{
		window.clear();
		
		sf::Event event;
		if(!inAction)
		{
			noMove=false, forward=false,backward=false, crouch=false, jump=false,jumpForward=false,jumpBackward=false,inAction=false, enMonte=true;punch=false,kick=false;
			if (sf::Joystick::isConnected(0))
			{
				punch=sf::Joystick::isButtonPressed(0, 0);
				kick=sf::Joystick::isButtonPressed(0, 1);
				controller0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
				controller0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
				//cout<<"x : "<<controller0_axisX<<"\t y : "<<controller0_axisY<<endl;
				if( (controller0_axisX > -40 && controller0_axisX < 40) && (controller0_axisY > -40 && controller0_axisY < 40))
				{
					noMove=true;
					forward=false;
					backward=false;
					jump=false;
					jumpForward=false;
					jumpBackward=false;
				}
				else if( (controller0_axisX > 40) && (controller0_axisY < 45 && controller0_axisY > -25) )
					forward=true;
				else if( (controller0_axisX < -40) && (controller0_axisY < 45 && controller0_axisY > -25) )
					backward=true;
				else if( (controller0_axisX>-40 && controller0_axisX<40) && (controller0_axisY<-40) )
					jump=true;
				else if( (controller0_axisX<=95 && controller0_axisX>=40) && (controller0_axisY<-40) )
					jumpForward=true;
				else if( (controller0_axisX>=-95 && controller0_axisX<=-40) && (controller0_axisY<-40) )
					jumpBackward=true;
				else if( (controller0_axisX>-40 && controller0_axisX<40) && (controller0_axisY>40) )
					crouch=true;
			}else
			{
				forward=sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
				backward=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
				jump=sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
				punch=sf::Keyboard::isKeyPressed(sf::Keyboard::A);
				if( (forward || backward) && punch)
				{
					forward=false;
					backward=false;
					punch=true;
				}
				kick=(sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
				if( (forward || backward) && kick)
				{
					forward=false;
					backward=false;
					kick=true;
				}else if(jump && forward)
				{
					jumpForward=true;
					jump=false;
					forward=false;
				}else if(jump && backward)
				{
					jumpBackward=true;
					jump=false;
					backward=false;
				}
			}
			if(kick && punch)
			{
				kick=false;
				punch=true;
			}
			else if(punch && (forward || backward))
			{
				punch=true;
				forward=false;
				backward=false;
			}else if(kick && (forward || backward))
			{
				kick=true;
				forward=false;
				backward=false;
			}
			if(!forward && !backward && !jump && !jumpForward && !jumpBackward && !inAction && !enMonte && !punch && !kick)
				noMove=true;
		}

		if(!backward)
			xBackward=-1;
		if(!crouch)
			xCrouch=-1;

		if(forward)
		{
			sf::Time elapsedForward = clockAnim.getElapsedTime();
			timeanim = elapsedForward.asMilliseconds();
			if(timeanim > 70 || xForward==-1){
				xForward++;
				clockAnim.restart();
			}
			perso.moveRight(background,xForward);
			
			
			if(xForward==12)
				xForward=1;
			
		}else if(backward){
			sf::Time elapsedBackward = clockAnim.getElapsedTime();
			timeanim = elapsedBackward.asMilliseconds();
			if(timeanim > 50 || xBackward==-1)
			{
				xBackward++;
				clockAnim.restart();
			}
			perso.moveLeft(background,xBackward);

		}else if(crouch)
		{
			sf::Time elapsedCrouch = clockAnim.getElapsedTime();
			timeanim = elapsedCrouch.asMilliseconds();
			if(timeanim > 50 || xCrouch==-1)
			{
				xCrouch++;
				clockAnim.restart();
			}
			perso.crouch(background,xCrouch);

		}else if(jump){
			inAction=true;
			sf::Time elapsedJump = clockAnim.getElapsedTime();
			timeanim = elapsedJump.asMilliseconds();
			if(jump==-1 || jump==6)
				xJump++;
			else if(xJump==0 || xJump==6)
			{
				if(timeanim > 150){
					xJump++;
					clockAnim.restart();
				}
			}else{
				if(timeanim > 100){
					xJump++;
					clockAnim.restart();
				}
			}
			if(xJump>=0)
				perso.jumpNoMove(background,xJump);
			if(xJump==7)
			{
				inAction=false;
				xJump=-1;
			}
			
		}else if(jumpForward){   //saut vers l'avant
			
			inAction=true;
			sf::Time elapsedJumpForward = clockAnim.getElapsedTime();
			timeanim = elapsedJumpForward.asMilliseconds();
			if(enMonte)
			{	
				if(xJumpDirection==5 || (xJumpDirection==5 && !enMonte))
					xJumpDirection--;
				else if(xJumpDirection==4)
				{
					if(timeanim > 100){
						xJumpDirection--;
						clockAnim.restart();
					}
				}else{
					if(timeanim > 100){
						xJumpDirection--;
						clockAnim.restart();
					}
				}
			}else{
				if(xJumpDirection==3)
				{
					if(timeanim > 100){
						xJumpDirection++;
					}
				}else{
					if(timeanim > 100){
						xJumpDirection++;
					}
				}
			}
			perso.jumpMoveRight(background,xJumpDirection,enMonte);
			if(xJumpDirection==0)
			{
				enMonte=false;
				xJumpDirection=1;
			}else if(xJumpDirection==5 && !enMonte)
			{
				inAction=false;
				jumpForward=false;
				enMonte=true;
				perso.reset(window,9);
			}

		}else if(jumpBackward){
			inAction=true;
			sf::Time elapsedJumpForward = clockAnim.getElapsedTime();
			timeanim = elapsedJumpForward.asMilliseconds();
			if(enMonte)
			{	
				if(xJumpDirection==5 || (xJumpDirection==4 && !enMonte))
					xJumpDirection--;
				else if(xJumpDirection==4)
				{
					if(timeanim > 100){
						xJumpDirection--;
						clockAnim.restart();
					}
				}else{
					if(timeanim > 100){
						xJumpDirection--;
						clockAnim.restart();
					}
				}
			}else{
				if(xJumpDirection==3)
				{
					if(timeanim > 100){
						xJumpDirection++;
						clockAnim.restart();
					}
				}else{
					if(timeanim > 100){
						xJumpDirection++;
						clockAnim.restart();
					}
				}
			}
			perso.jumpMoveLeft(background,xJumpDirection,enMonte);
			if(xJumpDirection==0)
			{
				enMonte=false;
				xJumpDirection=1;
			}else if(xJumpDirection==5 && !enMonte)
			{
				inAction=false;
				jumpBackward=false;
				enMonte=true;
				perso.reset(window,9);
			}

		}else if(punch){
			inAction=true;
			sf::Time elapsedPunch = clockAnim.getElapsedTime();
			timeanim = elapsedPunch.asMilliseconds();
			if(timeanim > 70 || xPunch==-1){
				xPunch++;
				clockAnim.restart();
			}
			if(xPunch>=0)
				perso.punch(window,xPunch);

			if(xPunch==5)
			{
				xPunch=-1;
				inAction=false;
			}

		}else if(kick)
		{
			inAction=true;
			sf::Time elapsedKick = clockAnim.getElapsedTime();
			timeanim = elapsedKick.asMilliseconds();
			if(timeanim > 70 || xKick==-1){
				xKick++;
				clockAnim.restart();
			}
			if(xKick>=0)
				perso.kick(window,xKick);

			if(xKick==7)
			{
				xKick=-1;
				inAction=false;
			}
		}else{
			sf::Time elapsedNoMove = clockAnim.getElapsedTime();
			timeanim = elapsedNoMove.asMilliseconds();
			if(timeanim > 150 || xNoMove==-1){
				xNoMove++;
				clockAnim.restart();
			}
			perso.reset (background,xNoMove);
			
			
			if(xNoMove==9)
				xNoMove=-1;
		}


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.draw(background.getSprite());
        window.draw(background.getSol());
		window.draw(background.getWallLeft());
		window.draw(background.getWallRight());
        window.draw(perso.getSprite());
        window.draw(perso.getCorps());
        window.draw(perso.getBras());
        window.display();
	}
	return 0;
}