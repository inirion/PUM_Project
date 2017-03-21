/*
 * RocketLauncher.hpp
 *
 *  Created on: 22 maj 2016
 *      Author: Piotr Okoń
 */

#ifndef JNI_ROCKETLAUNCHER_HPP_
#define JNI_ROCKETLAUNCHER_HPP_

#include "Tower.hpp"

class RocketLauncher : public Tower{
private:
	virtual void setLevelParams();
public:
	static const int frameW = 256;
	static const int frameH = 232;
	RocketLauncher(sf::Vector2i pos);// konstruktor parametryczny ustawiający daną wieżyczkę na miejscu wskazanym przez wektor oraz inicjalizująca ją podstawowymi wartościami.
};

#endif /* JNI_ROCKETLAUNCHER_HPP_ */
