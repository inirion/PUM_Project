/*
 * FloatingDamage.hpp
 *
 *  Created on: 13 maj 2016
 *      Author: Piotr Okoń
 */

#ifndef FLOATINGDAMAGE_HPP_
#define FLOATINGDAMAGE_HPP_

#include "Positionable.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include "Conf.hpp"
#include <cmath>
#include "log.hpp"
class FloatingDamage : public Positionable, public sf::Drawable{
private:
	sf::Text text;
	bool enemyFlying;
	bool toDel;
	bool scaling;
	int damageAmount;
	int hits;
	int delay;
	int lastTime;
	float deltaX;
	float deltaY;
	float startTime;
public:
	FloatingDamage(int damage, sf::Vector2f pos, bool flying, int fontSize = 20) :
		enemyFlying(flying),
		toDel(false),
		scaling(true),
		damageAmount(damage),
		hits(1),
		delay(15),
		lastTime(CLOCKASMS),
		deltaX(0.0f),
		deltaY(0.0f),
		startTime(CLOCKASSEC)
	{
		position = pos;
		if(enemyFlying) position.y -= 78;
		deltaX = 50.f * std::sin(Conf::clock.getElapsedTime().asSeconds() * 4);
		position.x += deltaX;
		std::string s = std::to_string(damageAmount);
		text.setString(s);
		text.setPosition(position);
		text.setFont(Conf::fMono);
		text.setCharacterSize(fontSize);
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	void update(sf::Vector2f pos);// metoda odświeżająca dany obiekt.
	inline bool isToDel() const {return toDel;}
	void increaseDmg(int dmg);// metoda zwiększająca obrażenia
};

#endif
