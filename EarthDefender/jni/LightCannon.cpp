/*
 * LightCannon.cpp
 *
 *  Created on: 09.09.2016
 *      Author: jakub
 */

#include "LightCannon.hpp"

void LightCannon::setLevelParams(){
	switch(level){
	case 1:
		flashHeightShift[0]=-30;
		flashRadius[0]=90;
		flashRadiusTransition[0]=32;
		flashScaleTransition[0]=3;
		flashSprite[0].getRect().setSize(sf::Vector2f(20,10));
		flashSprite[0].getRect().setOrigin(sf::Vector2f(10,5));

		break;
	case 2:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;

		flashRadius[0]=98;
		flashScaleTransition[0]=4;

		flashRadius[1]=98;
		flashRadiusTransition[1]=32;
		flashScaleTransition[1]=4;
		flashSprite[1].getRect().setSize(sf::Vector2f(20,10));
		flashSprite[1].getRect().setOrigin(sf::Vector2f(10,5));

		break;

	case 3:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;

		flashRadius[0]=106;
		flashRadius[1]=106;
		flashScaleTransition[0]=5;
		flashScaleTransition[1]=5;
		flashAngleShift[0]=-0.1;
		flashAngleShift[1]=0.1;

		flashHeightShift[2]=4;
		flashRadius[2]=106;
		flashRadiusTransition[2]=28;
		flashScaleTransition[2]=5;
		flashSprite[2].getRect().setSize(sf::Vector2f(20,10));
		flashSprite[2].getRect().setOrigin(sf::Vector2f(10,5));

		break;
	}
}
LightCannon::LightCannon(sf::Vector2i pos) : Tower(pos){// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
	originY=0.703947368421;
	setFrameDimension(sf::Vector2i(frameW,frameH));
	text=S::tower_lightcannon;
	towerType = LAND;
	range=2.5f;
	minDmg=20;
	maxDmg=60;
	flashDelay=200;
	newBulletDelay=800;
	shotSoundName=S::snd_cannon+std::to_string(rand()%4+1);
	setLevelParams();
	refreshAnim();
	sprite.setScale(0.9,0.9);
}

