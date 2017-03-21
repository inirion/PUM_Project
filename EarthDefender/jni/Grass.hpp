/*
 * Grass.hpp
 *
 *  Created on: 2 maj 2016
 *      Author: Grzegorz Kokoszka
 */

#ifndef GRASS_HPP_
#define GRASS_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Positionable.hpp"
#include "Textures.hpp"
#include "Conf.hpp"

class Grass: public sf::Drawable, public Positionable {
private:
	const int frame_count = 48;

	sf::RectangleShape grass;
	sf::Vector2i frameDimension;
	int currentFrame;
	float frameDelay;
	float lastFrameTime;
	sf::Text Text;
public:
	Grass(sf::Vector2i pos) ://konstruktor parametryczny ustawiający wszystkie wartości wymagane do działania klasy.
			frameDimension(sf::Vector2i(256, 152)), currentFrame(0), frameDelay(
					50.0f) {
		grass.setTexture(&Textures::get("map.grassanim"));
		sf::Vector2f temp;
		int offset;
		if (pos.x % 2 == 0)
			offset = Conf::TILE_WIDTH / 2;
		else
			offset = 0;
		temp.x = pos.y * Conf::TILE_WIDTH + offset;
		temp.y = pos.x * Conf::TILE_HEIGHT / 2 - Conf::TILE_HEIGHT;
		grass.setPosition(temp);
		position = temp;
		xyPosition = pos;
		grass.setSize(sf::Vector2f(200.0f, 118.75f));
		grass.setTextureRect(
				sf::IntRect(0, 0, frameDimension.x, frameDimension.y));
		lastFrameTime = Conf::clock.getElapsedTime().asMilliseconds();
		grass.setOrigin(0.f, 10.0f);
	}
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	void update();// metoda odświeżająca dany obiekt.
};

#endif /* GRASS_HPP_ */
