#ifndef SOUNDS_HPP_
#define SOUNDS_HPP_

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "S.hpp"

class Sounds{	//statyczna klasa dźwięków
private:
	static std::map<std::string, sf::SoundBuffer> map;
	static bool inited;


public:
	static void init();// metoda inicjalizująca wektor map dźwiękami.
	static sf::SoundBuffer& get(std::string id);//zwraca referencje na wybrany obiekt w zainicjalizowanej mapie.
};


#endif /* SOUNDS_HPP_ */
