/*
 * Bullet.cpp
 *
 *  Created on: 28 kwi 2016
 *      Author: Piotr Oko�
 */
#define _USE_MATH_DEFINES
#include "Bullet.hpp"
#include <cmath>

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(bullet, states);

	/*sf::CircleShape cs;
	cs.setFillColor(sf::Color::Blue);
	cs.setRadius(5.0f);
	cs.setOrigin(cs.getRadius(), cs.getRadius());
	cs.setPosition(towerPos);
	target.draw(cs, states);

	sf::Vector2f temp(towerPos.x + (targetEnemy->getPosition().x - towerPos.x) / 2, towerPos.y - 100.f);
	cs.setPosition(temp);
	target.draw(cs, states);

	sf::Vector2f enemyPos = targetEnemy->getPosition();
	enemyPos.y -= 78;
	cs.setPosition(enemyPos);
	target.draw(cs, states);*/
}

void Bullet::update(){ 
	int diff = Conf::clock.getElapsedTime().asMilliseconds() - lastMoveTime;
	if(diff >= speed){

		sf::Vector2f targetPos = targetEnemy->getAnim().getPosition();
		getParabolaParams();
		float step = std::fabs(towerPos.x - targetPos.x) / 50.f;
		step = (diff * step) / speed;


		
		if (targetEnemy->isFlying()) targetPos.y -= 78;
		if(position.x > targetPos.x - 15.0f && position.x <targetPos.x + 15.0f && position.y > targetPos.y - 15.0f && position.y <targetPos.y + 15.0f){
			enemyShooted = true;
			return;
		}
		float tempX = position.x;
		if(targetPos.x > position.x){
			if(targetPos.x - position.x < step)
				tempX = targetPos.x;
			else
				tempX += step;
		}
		else if(targetPos.x < position.x){
			if(targetPos.x - position.x > step)
				tempX = targetPos.x;
			else
				tempX -= step;
		}

		float newAngle = std::atan((getY(tempX + 0.01f) - getY(tempX)) / 0.01f);
		newAngle = ((newAngle * 180) / M_PI);
	
		if (targetPos.x < towerPos.x) newAngle += 180;
		if (std::fabs(angle - newAngle) > 3.f) {
			bullet.rotate(newAngle - angle);
			angle = newAngle;
		}
		
		
		position.y = getY(tempX);
		position.x = tempX;
		bullet.setPosition(position);
		lastMoveTime = Conf::clock.getElapsedTime().asMilliseconds();
	}
}

void Bullet::getParabolaParams(){
	sf::Vector2f p1 = towerPos;
	sf::Vector2f p2(towerPos.x + (targetEnemy->getAnim().getPosition().x - towerPos.x) / 2, towerPos.y - 100.f);;
	sf::Vector2f p3 = targetEnemy->getAnim().getPosition();
	if (targetEnemy->isFlying()) p3.y -= 78;
	float x1 = p1.x;
	float y1 = p1.y;
	float x2 = p2.x;
	float y2 = p2.y;
	float x3 = p3.x;
	float y3 = p3.y;

	double denom = (x1 - x2) * (x1 - x3) * (x2 - x3);
	A = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2)) / denom;
	B = (x3*x3 * (y1 - y2) + x2*x2 * (y3 - y1) + x1*x1 * (y2 - y3)) / denom;
	C = (x2 * x3 * (x2 - x3) * y1 + x3 * x1 * (x3 - x1) * y2 + x1 * x2 * (x1 - x2) * y3) / denom;

	
}

float Bullet::getY(float x)
{
	return A * x * x + B * x + C;
}

