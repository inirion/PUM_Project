/*
 * Base.cpp
 *
 *  Created on: 3 maj 2016
 *      Author: Piotr Okoń
 */

#include "Base.hpp"
#include <cmath>
#include <string>

void Base::setBasePosition(sf::Vector2i pos){
	xyPosition = pos;

	sf::Vector2f temp;
	int offset;
	if(pos.x % 2 == 0)
		offset = Conf::TILE_WIDTH/2;
	else
		offset = 0;
	temp.x = pos.y * Conf::TILE_WIDTH + offset;
	temp.y = pos.x * Conf::TILE_HEIGHT / 2;

	position = temp;

	temp.y-=32;
	anim.getRect().setPosition(temp);
}
void Base::update(std::vector<Enemy*> &enemies){
	LOGF("Base::update");

	anim.update();

	for(auto i = enemies.begin(); i != enemies.end(); ++i){
		if(isEnemyInRange(*i)){
			int HP = (*i)->getDamage();
			std::string s = std::to_string(HP);
			sendMessage("basehp", s);
			(*i)->setHP(-10000);
			if (floatingDmg.size() > 0) {
			if (Conf::clock.getElapsedTime().asSeconds() - lastHitTime < 1.f) {
				floatingDmg[floatingDmg.size() - 1].increaseDmg(HP);

			}
			else {
				floatingDmg.push_back(
						FloatingDamage(HP, position, false, 50));
				lastHitTime = Conf::clock.getElapsedTime().asSeconds();
				}
			}
			else {
				floatingDmg.push_back(
						FloatingDamage(HP, position, false, 50));
				lastHitTime = Conf::clock.getElapsedTime().asSeconds();
			}
		}
	}

	floatingDmg.erase(std::remove_if(floatingDmg.begin(), floatingDmg.end(), [](const FloatingDamage& fd) {return fd.isToDel(); }), floatingDmg.end());
	for (auto &fd : floatingDmg)
		fd.update(position);

}
void Base::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	float x=Conf::clock.getElapsedTime().asSeconds()*4;
	float sinx=std::sin(x);

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(4+4*std::fabs(sinx));
	circle.setOutlineColor(sf::Color(0,255,0,128+127*std::fabs(sinx)));
	circle.setRadius(Conf::TILE_WIDTH / 2 + range * Conf::TILE_WIDTH + 4*sinx);
	circle.setPosition(position);
	circle.setScale(1.0f, 0.5f);
	circle.setPointCount(64);

	circle.setRadius(circle.getRadius()-60);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	target.draw(circle);

	circle.setRadius(circle.getRadius()+30);
	circle.setOutlineColor(circle.getOutlineColor()*sf::Color(255,255,255,64));
	circle.setOutlineThickness(circle.getOutlineThickness()+6);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	target.draw(circle);

	circle.setOutlineColor(circle.getOutlineColor()*sf::Color(255,255,255,64));
	circle.setRadius(circle.getRadius()+30);
	circle.setOutlineThickness(circle.getOutlineThickness()+6);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	target.draw(circle);

	target.draw(anim, states);

	for (const auto &fd : floatingDmg)
		target.draw(fd, states);
}
bool Base::isEnemyInRange(Enemy* e){
	if(e->getHP()<=0) return false;
	sf::Vector2f center;
	center.x = position.x;
	center.y = position.y + Conf::TILE_HEIGHT/2;

	sf::Vector2f radius;
	radius.x = Conf::TILE_WIDTH / 2 + range * Conf::TILE_WIDTH;
	radius.y = radius.x / 2;

	sf::Vector2f pos = e->getAnim().getPosition();
	sf::Vector2f normalized(pos.x - center.x, pos.y - center.y);
	return ((normalized.x * normalized.x)/ (radius.x * radius.x)) + ((normalized.y * normalized.y) / (radius.y * radius.y)) <= 1.0;
}
