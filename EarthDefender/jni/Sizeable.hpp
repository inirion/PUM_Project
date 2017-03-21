#ifndef SIZEABLE_HPP_
#define SIZEABLE_HPP_
#include <SFML/Graphics.hpp>

class Sizeable{
protected:
	sf::Vector2f size;

public:
	inline sf::Vector2f getSize(){return size;}//metoda zwracająca wielkość ustawioną wcześniej w klasie.
	inline void setSize(sf::Vector2f val){ size=val; }// metoda ustawiająca wielkość.
};

#endif
