/*
 * LightHoverCraft.hpp
 *
 *  Created on: 30 kwi 2016
 *      Author: Grzegorz Kokoszka
 */

#ifndef LIGHTHOVERCRAFT_HPP_
#define LIGHTHOVERCRAFT_HPP_

#include "Enemy.hpp"

class LightHoverCraft : public Enemy{
public:
	LightHoverCraft(Path *path) : Enemy(path,false){// konstruktor parametryczny ustawiający podstawowe wartości przeciwnika.
		vehicleSprite.setTexture(S::tex_enemy_lighthovercraft);
		speed = 200.0f;

		distortionFunc=distortedPosition;
		text=S::enemy_lighthovercraft;
		lmsg.objectname=text;
		enemyType = LAND;
		damage = 50.f;
	}

	static inline sf::Vector2f distortedPosition(sf::Vector2f pos, float seed){// statyczna metoda obliczająca odchylenie na drodze wywołująca bardziej realistyczne poruszanie się przeciwnika po drodze.
		sf::Vector2f vec=pos;
		double x=seed+Conf::clock.getElapsedTime().asSeconds()*4;
		vec.y+=6*std::sin(x);
		return vec;
	}
};

#endif /* LIGHTHOVERCRAFT_HPP_ */
