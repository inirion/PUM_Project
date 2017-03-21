/*
 * Animation.hpp
 *
 *  Created on: 2 maj 2016
 *      Author: Piotr Okoń
 */

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include "Conf.hpp"
#include "log.hpp"
#include "Positionable.hpp"
#include "Textureable.hpp"
#include "S.hpp"

class Animation : public Positionable, public sf::Drawable, public Textureable{
protected:
	sf::RectangleShape rect;
	sf::Vector2f frameDimension;
	int rows;
	int cols;
	int currentFrame;
	int maxFrames;
	int delay;
	int lastTime;
	bool oneTime;
public:
	Animation(int rows=1, int cols=1, std::string texId=S::tex_unknown, float delay=100):
	rows(rows),
	cols(cols),
	currentFrame(0),
	maxFrames(rows * cols),
	delay(delay),
	lastTime(CLOCKASMS),
	oneTime(false){
//		LOGD("FD X: %f FD Y: %f", frameDimension.x, frameDimension.y);
		setTexture(texId);
		refreshTexture();
		rect.setSize(sf::Vector2f(frameDimension.x, frameDimension.y));
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	virtual void update();// metoda odświeżająca dany obiekt.
	virtual void refreshTexture();// odświeżenie tekstury(zainicjowanie jej nowymi danymi które mogły się zmienić)
	virtual void setTexture(std::string tex);
	sf::RectangleShape& getRect(){return rect;}//getter zwracający referencję do utworzonego Recta obiektu.
	const sf::RectangleShape& getRect()const{return rect;}
	inline sf::Vector2f getFrameDimension()const{return frameDimension;}// getter zwracający floatowy wektor rozmiarów danej klatki animacji.
	inline int getMaxFrames()const{return maxFrames;}// getter zwracający maksymalną ilość klatek danej animacji.
	inline void setFrameDimension(sf::Vector2f v){frameDimension=v;}// setter podający jakie rozmiary ma posiadać klatka animacji
	inline void setRowsAndCols(int r, int c){rows=r; cols=c; maxFrames=r*c; refreshTexture();} // setter ustawiający dana animacja posiada wierszy i kolumn w pliku graficznym, ustawia również maksymalną ilość klatek oraz odświeża.
	inline void setFrame(int f){currentFrame=f; rect.setTextureRect(getFrameRect(currentFrame));}// setter ustawiający która klatka ma być aktywna.
	inline void setRandomFrame(){currentFrame=rand()%maxFrames; rect.setTextureRect(getFrameRect(currentFrame));}// setter ustawiający klatkę na losową.
	virtual inline void setPosition(sf::Vector2f val){ position=val; rect.setPosition(position); } // setter ustawiający pozycje danej animacji;
	virtual inline void move(sf::Vector2f val, float mul=1.0f){ position+=val*mul; rect.setPosition(position); }// metoda umożliwiająca przesuwanie się animacji o dany wektor floatowych wartości oraz mnożnik który odpowiada szybkości ruchu.
	inline int getCols()const{return cols;} //getter zwracający ilość kolumn danej animacji z pliku graficznego.
	inline int getRows()const{return rows;} //getter zwracający ilość wierszy danej animacji z pliku graficznego.
	sf::IntRect getFrameRect(int frame)const; //constowy getter zwracający sf::IntRect danej klatki animacji, metoda używana jedynie w tej klasie.
	inline void setOneTime(bool v){oneTime=v;}// setter boolowski ustawiający czy dana animacja ma wykonać się raz czy ma być odtwarzana od początku do końca trwania animacji.
	inline void setDelay(float d){delay=d;} // setter ustawiający opóźnienie między klatkami danej animacji.
	inline int getCurrentFrame()const{return currentFrame;}// constowy getter zwracający klatkę animacji która jest teraz aktywna.
	inline bool isLastFrame()const{return currentFrame >= maxFrames-1;}// metoda boolowka zwracająca czy dana klatka jest ostatnia czy nie.
	inline void start(){currentFrame=0; lastTime=CLOCKASMS;}// metoda ustawiająca klatki animacji na początek.
};

#endif /* ANIMATION_HPP_ */
