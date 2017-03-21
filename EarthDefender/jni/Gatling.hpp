/*
 * Gatling.hpp
 *
 *  Created on: 23 kwi 2016
 *      Author: Piotr Okoń
 */

#ifndef GATLING_HPP_
#define GATLING_HPP_

#include "Tower.hpp"
#include "Sounds.hpp"
class Gatling : public Tower{
private:
	virtual void setLevelParams();// metoda prywatna ustawiająca wartości wieżyczki w zależności od poziomu.
public:
	static const int frameW = 176;
	static const int frameH = 232;
	Gatling(sf::Vector2i pos);// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
};

#endif /* GATLING_HPP_ */
