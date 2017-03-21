/*
 * Vec3Enemy.hpp
 *
 *  Created on: 15 maj 2016
 *      Author: Grzegorz Kokoszka
 */

#ifndef VEC3ENEMY_HPP_
#define VEC3ENEMY_HPP_

class Vec3Enemy {
private:
	sf::Vector2f pos;
	int frame;
public :
	Vec3Enemy(sf::Vector2f pos, int frame) :
			pos(pos), frame(frame) {
	}
	sf::Vector2f getPosition(){//metoda zwracająca pozycję.
		return pos;
	}
	int getFrame(){//metoda zwracająca przetrzymywany rodzaj klatki na danej pozycji.
		return frame;
	}
};

#endif /* VEC3ENEMY_HPP_ */
