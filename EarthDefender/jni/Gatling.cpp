/*
 * Gatling.cpp
 *
 *  Created on: 09.09.2016
 *      Author: jakub
 */

#include "Gatling.hpp"

void Gatling::setLevelParams(){
	switch(level){
	case 1:
		flashHeightShift[0]=-55;
		flashRadius[0]=48;
		flashRadiusTransition[0]=10;
		flashScaleTransition[0]=0.5;
		flashSprite[0].getRect().setSize(sf::Vector2f(16,16));
		flashSprite[0].getRect().setOrigin(sf::Vector2f(8,8));
		break;
	case 2:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;

		flashAngleShift[0]=0.166f;
		flashHeightShift[1]=-55;
		flashRadius[1]=48;
		flashRadiusTransition[1]=10;
		flashScaleTransition[1]=0.5;
		flashSprite[1].getRect().setSize(sf::Vector2f(16,16));
		flashSprite[1].getRect().setOrigin(sf::Vector2f(8,8));
		flashAngleShift[1]=-0.166f;

		break;

	case 3:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;

		flashHeightShift[2]=-75;
		flashRadius[2]=48;
		flashRadiusTransition[2]=10;
		flashScaleTransition[2]=0.5;
		flashSprite[2].getRect().setSize(sf::Vector2f(16,16));
		flashSprite[2].getRect().setOrigin(sf::Vector2f(8,8));
		flashAngleShift[2]=0.f;

		break;
	}
}
Gatling::Gatling(sf::Vector2i pos) : Tower(pos){// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
	originY=0.801724137931;
	setFrameDimension(sf::Vector2i(frameW,frameH));
	text=S::tower_gatling;
	towerType = AIR;
	range=2.5;
	minDmg=5;
	maxDmg=15;
	flashDelay=50;
	newBulletDelay=100;
	shotSoundName=S::snd_fastshot+std::to_string(rand()%6+1);
	setLevelParams();
	refreshAnim();
	sprite.setScale(0.62,0.62);
}
