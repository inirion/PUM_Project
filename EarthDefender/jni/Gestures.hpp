#ifndef GESTURES_HPP_
#define GESTURES_HPP_

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Conf.hpp"
#include "log.hpp"

class Gestures{
public:
	enum GestureAction{
		NoAction,
		Slide,
		Pinch,
		FastTap,
		Hold,
		Locked
	};

private:
	static GestureAction gestureAction;
	static bool holding[2];
	static float holdStartTime;
	static sf::Vector2f holdPoint[2];
	static sf::Vector2i holdPointI[2];
	static sf::Vector2f slideSpeed;
	static int pinchVal;
	static bool locked;

public:
	static void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	static inline GestureAction get(){	LOGF("Gestures::get"); if(!locked)return gestureAction; else return Locked;}// metoda zwracająca rodzaj gestu wykonywanego na ekranie.
	static inline void clear(){gestureAction=NoAction;}// ustawienie gestu na bez akcji.

	static inline bool getHold(size_t id){
		if(id<2){
			return holding[id];
		}
		return false;
	}
	static inline sf::Vector2f getHoldPoint(size_t id){
		if(id < 2){
			return holdPoint[id];
		}
		return sf::Vector2f();
	}
	static inline sf::Vector2i getHoldPointI(size_t id){
		if(id < 2){
			return holdPointI[id];
		}
		return sf::Vector2i();
	}
	static inline sf::Vector2f getSlideSpeed(){return slideSpeed;}
	static int getPinchVal(){return pinchVal;}
	static void lock(){locked=true;}

};

#ifndef NONANDROID
	#define SFGETPOINTERPOSITION(i) sf::Touch::getPosition(i,rw)
	#define SFISPOINTERDOWN(i) sf::Touch::isDown(i)
#else
	#define SFGETPOINTERPOSITION(i) sf::Mouse::getPosition(rw)
	#define SFISPOINTERDOWN(i) sf::Mouse::isButtonPressed(sf::Mouse::Left)
#endif

#endif /* GESTURES_HPP_ */
