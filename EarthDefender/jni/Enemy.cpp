/*
 * Enemy.cpp
 *
 *  Created on: 25 kwi 2016
 *      Author: Grzegorz Kokoszka
 */

#include "Enemy.hpp"
#include "Map.hpp"
#include "log.hpp"

std::map<std::string, std::string> Enemy::enemyPrices;
bool Enemy::enemyPricesInited = false;


Enemy::Enemy(Path *path, bool f) :
	Observable(S::class_enemy,"enemy","map"),
	distortionFunc(defDistort),
	enemyType(LAND),
	flying(f),
	erase(false),
	exit(false),
	destroyed(false),
	damage(1),
	maxHP(1000),
	hp(1000),
	estimatedHP(maxHP),
	speed(0.0f),
	number(0.0f),
	lastFrameTime(CLOCKASMS),
	lastHitTime(CLOCKASSEC),
	seed(rand() % 10000 / 1000.f)
{
	enabled=false;

	sf::Vector2f ss(100.0f, 100.0f);
//		sprite.setSize(ss);


	vehicleSprite.setRowsAndCols(4,2);
	vehicleSprite.getRect().setSize(ss);
	sf::Vector2f temp;

	int offset;
	sf::Vector2i pos = path->getStart();
	if (pos.x % 2 == 0)
		offset = Conf::TILE_WIDTH / 2;
	else
		offset = 0;
	temp.x = pos.y * Conf::TILE_WIDTH + offset + ss.x;
	temp.y = pos.x * Conf::TILE_HEIGHT / 2 + ss.y * 0.5;

//		sprite.setPosition(temp);
	vehicleSprite.setPosition(temp);
	if (!flying)
		vehicleSprite.getRect().setOrigin(ss.x / 2, ss.y / 2); //sprite.setOrigin(ss.x / 2, ss.y / 2);
	if (flying)
		vehicleSprite.getRect().setOrigin(ss.x / 2, (ss.y * 3) / 2);//sprite.setOrigin(ss.x / 2, (ss.y * 3) / 2);

	vehicleSprite.setPosition(temp);
	vehicleSprite.setXYPosition(pos);

	text = "enemy";
	explodeSprite.setTexture("fx.explode");
	explodeSprite.setRowsAndCols(6, 2);

	ss.x*=2;
	ss.y*=2;

	explodeSprite.getRect().setSize(ss);
	explodeSprite.getRect().setOrigin(sf::Vector2f(ss.x/2, ss.x/2));
	explodeSprite.getRect().setRotation(rand()%360);
	explodeSprite.getRect().setFillColor(sf::Color(200+55*(rand()%100/100.0f),240+15*(rand()%100/100.0f),255));
	explodeSprite.setDelay(33);
	explodeSprite.setOneTime(true);
}
void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (enabled) {
		if (hp >=0) {
			if(!destroyed){
				target.draw(vehicleSprite, states);

				for (const auto &fd : floatingDmg)
					target.draw(fd, states);
				sf::RectangleShape hpBar;
				sf::Vector2f pos = vehicleSprite.getPosition();
				if (!flying)
					hpBar.setPosition(pos.x - 50, pos.y - vehicleSprite.getRect().getGlobalBounds().height);

				if (flying)
					hpBar.setPosition(pos.x - 50, pos.y - vehicleSprite.getRect().getGlobalBounds().height * 2);

				hpBar.setSize(sf::Vector2f(100.f, 10.f));
				hpBar.setOutlineThickness(3.f);
				hpBar.setOutlineColor(sf::Color::Black);
				hpBar.setFillColor(sf::Color::Transparent);
				target.draw(hpBar, states);

				hpBar.setSize(sf::Vector2f(100.f * (hp * 1.0f) / (maxHP * 1.0f), 10.f));
				hpBar.setOutlineColor(sf::Color::Transparent);
				hpBar.setTexture(&Textures::get("blend"));
				if (hp > maxHP * 0.8)
					hpBar.setFillColor(sf::Color::Green);
				else if (hp > maxHP * 0.5)
					hpBar.setFillColor(sf::Color::Yellow);
				else
					hpBar.setFillColor(sf::Color::Red);
				target.draw(hpBar, states);
			}
		} else {
			target.draw(explodeSprite, states);
		}
	}
}
void Enemy::revalidate(){
	sf::Vector2f pos = vehicleSprite.getPosition();
	sf::Vector2i ipos = vehicleSprite.getXYPosition();

	sf::Vector2i tmp = Map::coords2XYABS(pos.x, pos.y);
	if(tmp != ipos){
		std::string val=
				std::to_string(ipos.x)+" "+
				std::to_string(ipos.y)+" "+
				std::to_string(tmp.x)+" "+
				std::to_string(tmp.y);

		lmsg.changes[S::cmd_revalidate]=val;
		lmsg.sender=this;
		notifyListeners();

		vehicleSprite.setXYPosition(tmp);
	}
}
void Enemy::destroyIt(){
	if(destroyed) return;

	destroyed=true;
//	sf::Vector2f p = vehicleSprite.getRect().getPosition(); //sprite.getPosition();
//	sf::Vector2f l = //sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);

	explodeSprite.setPosition(vehicleSprite.getPosition());
	explodeSprite.getRect().setOrigin(vehicleSprite.getRect().getOrigin());

//	if (flying)
//		explodeSprite.setPosition(l);
//	if (!flying)
//		explodeSprite.setPosition(p);

	explodeSprite.start();
	explodeSprite.setFrame(0);
}
void Enemy::update(std::vector<Vec3Enemy> &positionVec3Enemy, sf::Vector2f basePos) {
	LOGF("Enemy::update");

	if (enabled) {
		if (destroyed) {
			explodeSprite.update();

			if (explodeSprite.isLastFrame()) erase = true;

		}else{
			revalidate();

			if (Conf::debugEnable) {
				vehicleSprite.getRect().setOutlineThickness(2);
				vehicleSprite.getRect().setOutlineColor(sf::Color::Red);
			} else if (!Conf::debugEnable) {
				vehicleSprite.getRect().setOutlineThickness(0);
			}

			floatingDmg.erase(std::remove_if(floatingDmg.begin(), floatingDmg.end(), [](const FloatingDamage& fd) {return fd.isToDel(); }), floatingDmg.end());
			
			number += speed * Conf::dtime;

			size_t id=std::floor(number);
			if (id < positionVec3Enemy.size()) {
				vehicleSprite.setPosition(positionVec3Enemy.at(id).getPosition());
				vehicleSprite.setFrame(positionVec3Enemy.at(id).getFrame());
			}else{
				vehicleSprite.setPosition(basePos);
			}

			sf::Vector2f pos = vehicleSprite.getPosition();

			for (auto &fd : floatingDmg)
				fd.update(pos);

//			sf::Vector2i v(currentFrame / 4 * frameDimension.x, currentFrame % 4 * frameDimension.y);
//			sprite.setTextureRect(sf::IntRect(v.x, v.y, frameDimension.x, frameDimension.y));
//			sprite.setPosition(distortionFunc(position, seed));
			vehicleSprite.setPosition(distortionFunc(pos, seed));

			lastFrameTime = CLOCKASMS;
		}
	}
}
void Enemy::hit(int HP) {
	hp -= HP;
	if (floatingDmg.size() > 0) {
		if (Conf::clock.getElapsedTime().asSeconds() - lastHitTime < 0.5f) {
			floatingDmg[floatingDmg.size() - 1].increaseDmg(HP);

		} else {
			floatingDmg.push_back(FloatingDamage(HP, distortionFunc(vehicleSprite.getPosition(), seed), flying));
			lastHitTime = CLOCKASSEC;
		}
	} else {
		floatingDmg.push_back(FloatingDamage(HP, distortionFunc(vehicleSprite.getPosition(), seed), flying));
		lastHitTime = CLOCKASSEC;
	}
}
void Enemy::refreshTexture(){
	vehicleSprite.refreshTexture();
	vehicleSprite.setFrame(vehicleSprite.getCurrentFrame());
	explodeSprite.refreshTexture();
	explodeSprite.setFrame(explodeSprite.getCurrentFrame());




//	Textureable::refreshTexture();
//	sprite.setTexture(texture);
//	frameDimension.x = frameDimensionAbsolute.x/Conf::textureDivisor;
//	frameDimension.y = frameDimensionAbsolute.y/Conf::textureDivisor;
}
