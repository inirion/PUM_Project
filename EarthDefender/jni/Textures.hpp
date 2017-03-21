#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "S.hpp"
#include "Conf.hpp"

class Textures{	//statyczna klasa tekstur
private:
	static std::map<std::string, sf::Texture> map;
	static bool inited;

public:
	static void init(bool force=false);// metoda inicjalizująca wszystkie tekstury potrzebne do gry, tekstury są przechowywane w mapie.
	static sf::Texture& get(std::string id);// metoda zwracająca referencje na daną teksturę.
};



#endif /* TEXTURES_HPP_ */
