/*
 * Coil.hpp
 *
 *  Created on: 23 kwi 2016
 *      Author: Piotr Okoń
 */

#ifndef COIL_HPP_
#define COIL_HPP_

#include "Tower.hpp"

class Coil : public Tower{
private:
	void setLevelParams();// metoda prywatna ustawiająca wartości wieżyczki w zależności od poziomu.
public:
	static const int frameW = 134;
	static const int frameH = 256;
	Coil(sf::Vector2i pos);// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawywymi wartościami.
//	virtual void lvlUp(){// wirtualna metoda zwiększająca poziom wieżyczki o jeden.
//		Tower::lvlUp();
//		setLevelParams();
//	}
};

#endif /* COIL_HPP_ */
