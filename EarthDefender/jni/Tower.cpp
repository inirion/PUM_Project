/*
 * Tower.cpp
 *
 *  Created on: 22 kwi 2016
 *      Author: Piotr Okoń
 */
#define _USE_MATH_DEFINES
#include "Tower.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "log.hpp"
#include "Sounds.hpp"

#define ATGHALF 26.5650511771
#define FRAMETORAD(F) ((F)*0.261799387799)

std::vector<std::map<std::string, std::string>> Tower::towerPrices;
bool Tower::towerPricesInited = false;


Tower::Tower(sf::Vector2i pos) :
	targetedEnemy(NULL),
	frameDimension(sf::Vector2i(256,256)),
	towerType(LAND),
	newTargetMethod(NEAREST),
	lockOnTarget(true),
	firing(false),
	usingBullet(false),
	currentFrame(0),
	minDmg(50),
	maxDmg(100),
	newBulletDelay(750),
	lastBulletTime(CLOCKASMS),
	lastFiringTime(lastBulletTime),
	lastFrameTime(lastBulletTime),
	flashDelay(200),
	level(1),
	angle(0.0f),
	range(0.0f),
	frameDelay(100.0f),
	newTargetLastTime(CLOCKASSEC),
	originY(0.5)
	{

	sf::Vector2f temp;
	int offset;
	if(pos.x % 2 == 0)
		offset = Conf::TILE_WIDTH/2;
	else
		offset = 0;
	temp.x = pos.y * Conf::TILE_WIDTH + offset + Conf::TILE_WIDTH/2;
	temp.y = pos.x * Conf::TILE_HEIGHT / 2 + Conf::TILE_HEIGHT/2;

	position = temp;
	xyPosition = pos;
	sprite.setPosition(temp);

	text="tower";
	for(size_t i=0; i<TOWER_MAXLEVEL; ++i){
		textures[i]=NULL;

		flashHeightShift[i]=0.0f;
		flashRadius[i]=0.0f;
		flashRadiusTransition[i]=0.0f;
		flashScaleTransition[i]=0.0f;
		flashAngleShift[i]=0.0f;

		flashSprite[i].setTexture("fx.muzzleflash");
		flashSprite[i].setRowsAndCols(6,2);
		flashSprite[i].getRect().setSize(sf::Vector2f(32,32));
		flashSprite[i].getRect().setOrigin(sf::Vector2f(16,16));
	}

	shotSound.setAttenuation(0.1);
	shotSound.setMinDistance(100);
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);

	if(firing && !usingBullet){
		for(size_t i=0; i<level; ++i){
			target.draw(flashSprite[i],states);
		}
	}
	if (usingBullet) {
			for(std::list<Bullet>::const_iterator i = bullets.begin(); i != bullets.end(); ++i){
				target.draw(*i, states);
			}
	}
}
bool Tower::targetExist(std::vector<Enemy*> &e, Enemy* eptr) {
	for (auto i = e.begin(); i != e.end(); ++i) {
		if (*i == eptr)
			return true;
	}
	return false;
}
void Tower::update(std::vector<Enemy*> &e) {
	if (!targetExist(e, targetedEnemy)) {
		targetedEnemy = NULL;
	}

	if(firing && !usingBullet){
		if(Conf::clock.getElapsedTime().asMilliseconds() - lastFiringTime >= flashDelay){
			firing=false;
		}else{
			if(!lockOnTarget && Conf::clock.getElapsedTime().asSeconds() - newTargetLastTime >= 0.5f)
				lookForNewTarget(e);

			sf::Vector2f p;

			for(size_t i=0; i<level; ++i){
				p=sprite.getPosition();
				p.y+=flashHeightShift[i];

				double fp=1.0*(flashDelay - (Conf::clock.getElapsedTime().asMilliseconds() - lastFiringTime))/flashDelay;
				double ang=FRAMETORAD((currentFrame-14)%TOWER_FRAME_COUNT);

				p.x+=std::sin(ang+flashAngleShift[i])*(flashRadius[i]+flashRadiusTransition[i]*(1.0-fp));
				p.y+=std::cos(ang+flashAngleShift[i])*(flashRadius[i]+flashRadiusTransition[i]*(1.0-fp))*0.5;

				double x=std::cos(ang);
				double y=std::sin(ang)*2;
				ang=atan2(x,y)-M_PI_2;

				if(towerType==AIR){
					flashSprite[i].getRect().setRotation((ang)*(180/M_PI) + 45.f*std::sin(ang));
					flashSprite[i].getRect().setScale(1.0+flashScaleTransition[i]*(1.0-fp),(1.0+flashScaleTransition[i]*(1.0-fp))*(0.333*-std::cos(ang)+0.666));
	//				LOGE("smod = %.2f ; rmod = %.2f",(0.333*-std::cos(ang)+0.666),   45.f*std::sin(ang));
				}else{
					flashSprite[i].getRect().setRotation((ang)*(180/M_PI));
					flashSprite[i].getRect().setScale(1.0+flashScaleTransition[i]*(1.0-fp),1.0+flashScaleTransition[i]*(1.0-fp));
				}

				flashSprite[i].getRect().setFillColor(sf::Color(255,255,255,255*fp));
				flashSprite[i].setPosition(p);
			}
		}
	}

	updateBullets(e);
	if (Conf::clock.getElapsedTime().asMilliseconds() - lastFrameTime
			>= frameDelay) {
		
		if (targetedEnemy == NULL) {
			lookForNewTarget(e);
			return;
		}
		if (!isEnemyInRange(targetedEnemy)) {
			targetedEnemy = NULL;
			return;
		}
		sf::Vector2f enemyPos = targetedEnemy->getAnim().getPosition();
		angle = std::atan2((position.x - enemyPos.x) / 2,
				(position.y - enemyPos.y));
		float mangle = (angle * (180 / M_PI)) + 180 + ATGHALF;
		int ang = std::round(mangle);

		angle = ((ang / 10) * 10 - 15) * (M_PI / 180);

		ang/=15;
		ang+=13;
		ang%=TOWER_FRAME_COUNT;

		currentFrame = ang;

		refreshTextureRect();
		lastFrameTime = Conf::clock.getElapsedTime().asMilliseconds();
	}

	if (targetedEnemy != NULL && Conf::clock.getElapsedTime().asMilliseconds() - lastBulletTime >= newBulletDelay) {
		if (targetedEnemy->getEstimatedHP() > 0) {
			lastBulletTime = Conf::clock.getElapsedTime().asMilliseconds();
			int dmg = rand() % (maxDmg - minDmg) + minDmg;
			if (usingBullet) {
				bullets.push_back(Bullet(position, targetedEnemy, dmg));
			}
			else {
				targetedEnemy->hit(dmg);
			}
			targetedEnemy->setEstimatedHP(targetedEnemy->getEstimatedHP() - dmg);

			lastFiringTime = Conf::clock.getElapsedTime().asMilliseconds();
			firing = true;

			shotSound.setVolume(Conf::gameSoundVolume*0.4f);

			sf::Vector2f sp=sprite.getPosition();
			sp=sp-Conf::vw.getCenter();

			sf::Vector3f v3;
			v3.x=sp.x;
			v3.y=sp.y;
			v3.z=10*Conf::zm*Conf::zm;

			float md=shotSound.getMinDistance();
			if( v3.x*v3.x+v3.y*v3.y+v3.z*v3.z < md*md){
				shotSound.setBuffer(Sounds::get(shotSoundName));
			}else{
				shotSound.setBuffer(Sounds::get(shotSoundName+"m"));
			}

			shotSound.setPosition(v3);
			shotSound.setPitch(0.98 + 0.04*(rand()%100)/100.f);

			while(shotSound.getStatus()!=sf::Sound::Stopped){
				shotSound.stop();
			}
			shotSound.play();
			for(size_t i=0; i<level; ++i){
				flashSprite[i].setRandomFrame();
			}
		}
		else
			targetedEnemy = NULL;
	}
}
bool Tower::isEnemyInRange(Enemy* &e) {
	sf::Vector2f center;
	center.x = position.x;
	center.y = position.y + Conf::TILE_HEIGHT / 2;

	sf::Vector2f radius;
	radius.x = Conf::TILE_WIDTH / 2 + range * Conf::TILE_WIDTH;
	radius.y = radius.x / 2;

	sf::Vector2f normalized(e->getAnim().getPosition().x - center.x,
			e->getAnim().getPosition().y - center.y);
	return ((normalized.x * normalized.x) / (radius.x * radius.x))
			+ ((normalized.y * normalized.y) / (radius.y * radius.y)) <= 1.0;
}
void Tower::lookForNewTarget(std::vector<Enemy*> &e) {
	/*if(newTargetMethod == LAST || newTargetMethod == NEAREST){
		float lastDist;
		for (auto i = e.begin(); i != e.end(); ++i) {
			if (isEnemyInRange(*i) && (*i)->getEstimatedHP() != 0 && (*i)->isEnabled()
					&& ((*i)->getType() == towerType || towerType==AIRANDLAND) && (*i)->getHP() > 0) {
				if(newTargetMethod == LAST || targetedEnemy == NULL){
					targetedEnemy = *i;
					lastDist = std::sqrt((position.x - (*i)->getPosition().x) * (position.x - (*i)->getPosition().x)) + ((position.y - (*i)->getPosition().y) * (position.y - (*i)->getPosition().y));
				}
				else if(newTargetMethod == NEAREST){
					float dist = std::sqrt((position.x - (*i)->getPosition().x) * (position.x - (*i)->getPosition().x)) + ((position.y - (*i)->getPosition().y) * (position.y - (*i)->getPosition().y));
					if(dist < lastDist){
						targetedEnemy = *i;
						lastDist = dist;
					}
				}
				if(newTargetMethod == LAST)
				break;
			}
		}
	}*/
	if(newTargetMethod == LAST){
		for (auto i = e.begin(); i != e.end(); ++i) {
			if (isEnemyInRange(*i) && (*i)->getEstimatedHP() != 0 && (*i)->isEnabled()
					&& ((*i)->getType() == towerType || towerType==AIRANDLAND) && (*i)->getHP() > 0) {
				targetedEnemy = *i;
				break;
			}
		}
	}
	else if(newTargetMethod == NEAREST){
		float lastDist;
		bool newEnemy = false;
		for(auto i = e.begin(); i != e.end(); ++i){
			if (isEnemyInRange(*i) && (*i)->getEstimatedHP() != 0 && (*i)->isEnabled() && ((*i)->getType() == towerType || towerType==AIRANDLAND) && (*i)->getHP() > 0) {
				sf::Vector2f pos = (*i)->getAnim().getPosition();

				if(!newEnemy){
					newEnemy = true;
					targetedEnemy = *i;
					lastDist = std::sqrt((position.x - pos.x) * (position.x - pos.x)) + ((position.y - pos.y) * (position.y - pos.y));
					continue;
				}
				float dist = std::sqrt((position.x - pos.x) * (position.x - pos.x)) + ((position.y - pos.y) * (position.y - pos.y));
				if(dist < lastDist){
					targetedEnemy = *i;
					lastDist = dist;
				}
			}
		}
	}
	else if(newTargetMethod == FIRST){
		for (auto i = e.rbegin(); i != e.rend(); ++i) {
			if (isEnemyInRange(*i) && (*i)->getEstimatedHP() != 0 && (*i)->isEnabled()
					&& ((*i)->getType() == towerType || towerType==AIRANDLAND) && (*i)->getHP() > 0) {
				targetedEnemy = *i;
				break;
			}
		}
	}
}
void Tower::updateBullets(std::vector<Enemy*> &e) {
	std::list<std::list<Bullet>::iterator> todel;

	for (std::list<Bullet>::iterator i = bullets.begin(); i != bullets.end();
			++i) {
		if (!targetExist(e, i->getTarget())) {
			todel.push_back(i);
			continue;
		}
		if (i->isEnemyShooted()) {
			Enemy *target = i->getTarget();
			
				target->hit(i->getDmg());

			todel.push_back(i);
		} else
			i->update();
	}
	for (auto &i : todel) {
		bullets.erase(i);
	}
}
void Tower::setFrameDimension(sf::Vector2i v){//ustawienie rozmiarów klatki na podane wartości.
	frameDimension=v;
	refreshTextureRect();
	sprite.setSize(sf::Vector2f(200.0f, 200.0f * frameDimension.y/frameDimension.x));
	sprite.setOrigin(sprite.getSize().x/2, sprite.getSize().y * originY);
}
void Tower::refreshTextureRect() {
	sf::IntRect ir = Conf::irCorrection(frameDimension);
	sf::Vector2i v(currentFrame / 6 * ir.width, currentFrame % 6 * ir.height);
	ir.left = v.x;
	ir.top = v.y;
	sprite.setTextureRect(ir);
}
void Tower::refreshAnim(){
	for(size_t i=0; i<TOWER_MAXLEVEL; ++i){
		flashSprite[i].refreshTexture();
		flashSprite[i].setFrame(flashSprite[i].getCurrentFrame());

		std::string str = S::tower;
		str+=".";
		str+=text;
		str+=".";
		str+=std::to_string(i+1);
		textures[i] = &Textures::get(str);
	}
	sprite.setTexture(textures[level-1]);
	refreshTextureRect();
}
