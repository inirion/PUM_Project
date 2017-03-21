#ifndef POSITIONABLE_HPP_
#define POSITIONABLE_HPP_
#include <SFML/Graphics.hpp>

class Positionable{
protected:
	sf::Vector2f position;
	sf::Vector2i xyPosition;

public:
	virtual ~Positionable(){}

	virtual inline sf::Vector2f getPosition() const {return position;}//metoda pobierająca współżędne ustaloną wcześniej w tej klasie.
	virtual inline sf::Vector2i getXYPosition() const {return xyPosition;}//metoda pobierająca pozycje x oraz y ustaloną wcześniej w tej klasie.
	virtual inline void setPosition(sf::Vector2f val){ position=val; }// ustawienie pozycji na daną wartośc.
	virtual inline void move(sf::Vector2f val, float mul=1.0f){ position+=val*mul; }// zmiana pozycji o daną wartośc względem ostatniej pozycji.
	virtual inline void setXYPosition(sf::Vector2i val){ xyPosition=val; }// ustawienie pozycji x oraz y na mapie.
};

#endif /* POSITIONABLE_HPP_ */
