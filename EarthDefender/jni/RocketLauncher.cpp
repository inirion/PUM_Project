/*
 * RocketLauncher.cpp
 *
 *  Created on: 09.09.2016
 *      Author: jakub
 */

#include "RocketLauncher.hpp"

void RocketLauncher::setLevelParams(){
	switch(level){
		case 1:

			break;

		case 2:
			minDmg*=1.5;
			maxDmg*=1.5;
			range*=1.1;
			newBulletDelay*=0.9;

			break;

		case 3:
			minDmg*=1.5;
			maxDmg*=1.5;
			range*=1.1;
			newBulletDelay*=0.9;

			break;
	}
}
RocketLauncher::RocketLauncher(sf::Vector2i pos) : Tower(pos){// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
	originY=0.724137931034;
	setFrameDimension(sf::Vector2i(frameW,frameH));
	text=S::tower_rocketlauncher;
	towerType = AIR;
	range=2.5;
	minDmg=20;
	maxDmg=30;
	flashDelay=200;
	newBulletDelay=2000;
	shotSoundName=S::snd_cannon+std::to_string(rand()%4+1);
	usingBullet = true;
	setLevelParams();
	refreshAnim();
	sprite.setScale(0.6,0.6);
}
