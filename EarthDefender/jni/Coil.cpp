/*
 * Coil.cpp
 *
 *  Created on: 09.09.2016
 *      Author: jakub
 */

#include "Coil.hpp"

void Coil::setLevelParams(){
	switch(level){
	case 1:
		flashHeightShift[0]=-62;
		flashRadius[0]=22;
		flashRadiusTransition[0]=0;
		flashScaleTransition[0]=1;
		flashHeightShift[0]=-120;
		break;
	case 2:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;
		newBulletDelay*=0.9;

		flashHeightShift[0]=-130;
		flashHeightShift[1]=-135;
		flashRadius[1]=22;
		flashRadiusTransition[1]=0;
		flashScaleTransition[1]=1;
		flashAngleShift[1]=-0.3;

		break;

	case 3:
		minDmg*=1.5;
		maxDmg*=1.5;
		range*=1.1;
		newBulletDelay*=0.9;

		flashHeightShift[0]=-135;
		flashHeightShift[1]=-140;
		flashHeightShift[2]=-145;

		flashRadius[2]=22;
		flashRadiusTransition[2]=0;
		flashScaleTransition[2]=1;
		flashAngleShift[2]=0.3;
		break;
	}
}
Coil::Coil(sf::Vector2i pos) : Tower(pos){// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawywymi wartościami.
	originY=0.84765625;
	setFrameDimension(sf::Vector2i(frameW,frameH));
	text=S::tower_coil;
	towerType = AIRANDLAND;
	range=1.5;
	minDmg=15;
	maxDmg=30;
	flashDelay=250;
	newBulletDelay=1000;
	shotSoundName=S::snd_electric+std::to_string(rand()%4+1);
	for(size_t i=0; i<TOWER_MAXLEVEL; ++i){
		flashSprite[i].setTexture(S::tex_fx_lightning);
		flashSprite[i].setRowsAndCols(6,2);
		flashSprite[i].getRect().setSize(sf::Vector2f(50,50));
		flashSprite[i].getRect().setOrigin(sf::Vector2f(25,0));
	}
	setLevelParams();
	refreshAnim();
	sprite.setScale(0.50,0.50);
}
