/*
 * LightCannon.hpp
 *
 *  Created on: 23 kwi 2016
 *      Author: Piotr Okoń
 */

#ifndef LIGHTCANNON_HPP_
#define LIGHTCANNON_HPP_

#include "Tower.hpp"

class LightCannon : public Tower{
private:
	virtual void setLevelParams();// metoda prywatna ustawiająca wartości wieżyczki w zależności od poziomu.
public:
	static const int frameW = 256;
	static const int frameH = 152;
	LightCannon(sf::Vector2i pos);// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
};
#endif /* LIGHTCANNON_HPP_ */
