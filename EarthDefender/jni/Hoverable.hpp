#ifndef HOVERABLE_HPP_
#define HOVERABLE_HPP_

#include <SFML/Graphics.hpp>
#include "Sizeable.hpp"
#include "Positionable.hpp"
#include "Conf.hpp"
#include "Gestures.hpp"
#include "log.hpp"

class Hoverable: public Sizeable{
protected:
	bool hover;
	float hoverTime;

public:
	Hoverable(): hover(false), hoverTime(0.0f){}

	inline bool isHover(){// metoda informująca o tym czy użytkownik znajduje się w obszarze danego obiektu.
		return hover;
	}
	void checkHover(sf::RenderWindow &rw, sf::Vector2f pos){// metoda aktualizująca pole hover
		if(!Conf::windowFocused){
			hover=false;
			return;
		}
		if(SFISPOINTERDOWN(0)){
			sf::Vector2f p=rw.mapPixelToCoords(SFGETPOINTERPOSITION(0));
			if(
					p.x > pos.x &&
					p.x < pos.x + size.x*Conf::gs*Conf::zm &&
					p.y > pos.y &&
					p.y < pos.y + size.y*Conf::gs*Conf::zm
			){
				hover=true;
				Conf::hoverPos = p;
				hoverTime=Conf::clock.getElapsedTime().asSeconds();

				Gestures::lock();
			}else{
				hover=false;
			}
		}else{
			hover=false;
		}
	}
};

#endif /* HOVERABLE_HPP_ */
