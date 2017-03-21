/*
 * Bullet.hpp
 *
 *  Created on: 28 kwi 2016
 *      Author: Piotr Okoń
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_
#include <SFML/Graphics.hpp>
#include "Positionable.hpp"
#include "Enemy.hpp"
#include "Conf.hpp"

class Bullet : public Positionable, public sf::Drawable{
private:
	sf::RectangleShape bullet;
	Enemy *targetEnemy;
	sf::Vector2f towerPos;
	bool enemyShooted;
	int dmg;
	int angle;
	int lastMoveTime;
	float speed;
	float A, B, C;

	void getParabolaParams();
	float getY(float x);
public:
	Bullet(sf::Vector2f pos, Enemy *t, int dmg) :
	targetEnemy(t),
	towerPos(pos),
	enemyShooted(false),
	dmg(dmg),
	angle(0),
	lastMoveTime(CLOCKASMS),
	speed(15.0f)
	{
		position = pos;
		bullet.setPosition(pos);
		//bullet.setRadius(20.0f);
		bullet.setTexture(&Textures::get(S::tex_rocket));
		bullet.setSize(sf::Vector2f(128.f, 128.f));
		bullet.setOrigin(64.f, 64.f);
		getParabolaParams();
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	inline bool isEnemyShooted(){return enemyShooted;}// metoda boolowka ukazująca czy dany przeciwnik został postrzelony.
	void update();// metoda odświeżająca dany obiekt.
	inline Enemy* getTarget(){return targetEnemy;}//metoda zwracająca wskaźnik na przeciwnika który został wybrany przez klasę pocisku.
	inline bool Collision(sf::FloatRect &enemy, sf::Vector2f bullet)//metoda sprawdzająca kolizję pomiędzy pociskiem a przeciwnikiem.
	{
		return enemy.contains(bullet);
	}
	inline int getDmg() const { return dmg; }// getter zwracający jakie obrażenia zostały zadane przez pocisk.
};

#endif /* BULLET_HPP_ */
