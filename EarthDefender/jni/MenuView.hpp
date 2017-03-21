#ifndef MENUVIEW_HPP_
#define MENUVIEW_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "HaveButtons.hpp"

class MenuView: public sf::Drawable, public Textable, public HaveButtons{
protected:

public:
	MenuView(std::string name=""):
		Textable(name)
	{}
	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
};

#endif /* MENUVIEW_HPP_ */
