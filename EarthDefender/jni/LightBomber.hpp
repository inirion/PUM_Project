/*
 * LightBomber.hpp
 *
 *  Created on: 4 maj 2016
 *      Author: Grzegorz Kokoszka
 */

#ifndef LIGHTBOMBER_HPP_
#define LIGHTBOMBER_HPP_


#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#include "Enemy.hpp"
#include "S.hpp"

class LightBomber : public Enemy{
public:
	LightBomber(Path *path) : Enemy(path,true){// konstruktor parametryczny ustawiający podstawowe wartości przeciwnika.
		//setTexture(S::tex_enemy_lightbomber);
		vehicleSprite.setTexture(S::tex_enemy_lightbomber);
		speed = 200.f;

		distortionFunc=distortedPosition;
		text=S::enemy_lightbomber;
		lmsg.objectname=text;
		enemyType = AIR;
		damage = 100.f;
	}

	static inline sf::Vector2f distortedPosition(sf::Vector2f pos, float seed){// statyczna metoda obliczająca odchylenie na drodze wywołująca bardziej realistyczne poruszanie się przeciwnika po drodze.
		sf::Vector2f vec=pos;
		double x=seed+Conf::clock.getElapsedTime().asSeconds()*2;
		vec.y+=10*std::sin(x)*std::sin(1.33*x)*std::sin(M_PI*x);
		return vec;
	}
};



#endif /* LIGHTBOMBER_HPP_ */
