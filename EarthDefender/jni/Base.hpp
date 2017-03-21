/*
 * Base.hpp
 *
 *  Created on: 3 maj 2016
 *      Author: Piotr Okoń
 */

#ifndef BASE_HPP_
#define BASE_HPP_

#include "Positionable.hpp"
#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include "Textures.hpp"
#include <list>
#include "Enemy.hpp"
#include "Observable.hpp"
#include "Conf.hpp"

class Base : public Positionable, public sf::Drawable, public Observable{
private:
	Animation anim;
	std::vector<FloatingDamage> floatingDmg;
	float range;
	float lastHitTime;

	bool isEnemyInRange(Enemy* e);
public:
	Base(/*sf::Vector2i pos=sf::Vector2i(0,0)*/):
		Observable(S::class_base, "base", "Map"),
		anim(4, 3, S::tex_map_base, 100.0f),
		range(0.75),
		lastHitTime(CLOCKASSEC)
	{
		anim.getRect().setOrigin(sf::Vector2f(anim.getFrameDimension().x/2, anim.getFrameDimension().y/2));
	}
	void update(std::vector<Enemy*> &e);// metoda odświeżająca dany obiekt.
	void setBasePosition(sf::Vector2i pos);// setter ustawiający bazę na dane kafelki na mapie.
	inline void clearDmg() { floatingDmg.clear(); }// metoda która czyści wektor floating dmg.
	inline void refreshAnim(){anim.refreshTexture();}// metoda odświeżająca animacje bazy.

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
};

#endif /* BASE_HPP_ */
