/*
 * Tower.hpp
 *
 *  Created on: 22 kwi 2016
 *      Author: Piotr Okoń
 */

#ifndef TOWER_HPP_
#define TOWER_HPP_

#define TOWER_FRAME_COUNT 24
#define TOWER_MAXLEVEL 3


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Positionable.hpp"
#include "Textures.hpp"
#include "Conf.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Textable.hpp"
#include "Observable.hpp"
#include "Animation.hpp"
#include "S.hpp"

enum NewTargetMethod{
	FIRST, LAST, NEAREST
};

class Tower :
		public sf::Drawable,
		public Positionable,
		public Textable{
protected:
	static std::vector<std::map<std::string, std::string>> towerPrices;
	static bool towerPricesInited;

	Enemy *targetedEnemy;
	Animation flashSprite[TOWER_MAXLEVEL];
	sf::Texture *textures[TOWER_MAXLEVEL];
	sf::RectangleShape sprite;
	sf::Sound shotSound;
	sf::Vector2i frameDimension;
	std::list<Bullet> bullets;
	std::string shotSoundName;
	EnemyType towerType;
	NewTargetMethod newTargetMethod;
	bool lockOnTarget;
	bool firing;
	bool usingBullet;
	int currentFrame;
	int minDmg;
	int maxDmg;
	int newBulletDelay;
	int lastBulletTime;
	int lastFiringTime;
	int lastFrameTime;
	int flashDelay;
	size_t level;
	float angle;
	float range;
	float frameDelay;	//w ms
	float newTargetLastTime;
	float originY;
	float flashHeightShift[TOWER_MAXLEVEL];
	float flashRadius[TOWER_MAXLEVEL];
	float flashRadiusTransition[TOWER_MAXLEVEL];
	float flashScaleTransition[TOWER_MAXLEVEL];
	float flashAngleShift[TOWER_MAXLEVEL];

	Tower(sf::Vector2i pos);
	virtual void setLevelParams()=0;
	void lookForNewTarget(std::vector<Enemy*> &e);//metoda wymuszająca szukanie nowego przeciwniki.
	void updateBullets(std::vector<Enemy*> &e);//metoda odświeżająca pociski.
	bool targetExist(std::vector<Enemy*> &e, Enemy* eptr);//metoda sprawdzająca czy dany przeciwnik jeszcze istnieje(możliwe że inna wieżyczka zabiła go wcześniej).
	bool isEnemyInRange(Enemy* &e);// metoda sprawdzająca czy przeciwnik jest w zasięgu wieżyczki.

public:
	static void initPrices() {//metoda inicjalizująca wartości ulepszeń wieżyczek.
		if (!towerPricesInited) {
			towerPricesInited = true;

			towerPrices.resize(3);

			towerPrices[0][S::tower_lightcannon] = "150";
			towerPrices[1][S::tower_lightcannon] = "300";
			towerPrices[2][S::tower_lightcannon] = "600";

			towerPrices[0][S::tower_gatling] = "200";
			towerPrices[1][S::tower_gatling] = "400";
			towerPrices[2][S::tower_gatling] = "800";

			towerPrices[0][S::tower_coil] = "300";
			towerPrices[1][S::tower_coil] = "600";
			towerPrices[2][S::tower_coil] = "1200";

			towerPrices[0][S::tower_rocketlauncher] = "300";
			towerPrices[1][S::tower_rocketlauncher] = "600";
			towerPrices[2][S::tower_rocketlauncher] = "1200";
		}
	}
	static int priceOf(std::string t, size_t level) {// metoda zwracająca wartość wieżyczki na danym poziomie jako wartość.
		--level;
		if (level < towerPrices.size() && towerPrices[level].find(t) != towerPrices[level].end()) {
			return std::stoi(towerPrices[level].at(t));
		}
		return 0;
	}
	static std::string priceOfS(std::string t, size_t level) {// metoda zwracająca wartość wieżyczki na danym poziomie jako string.
		--level;
		if (level < towerPrices.size() && towerPrices[level].find(t) != towerPrices[level].end()) {
			return towerPrices[level].at(t);
		}
		return S::zero;
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	virtual void update(std::vector <Enemy*> &e);// metoda odświeżająca dany obiekt.
	virtual void lvlUp(){if(!isMaxLevel()){sprite.setTexture(textures[++level-1]); setLevelParams();}}//metoda podmieniająca teksturę po podniesieniu poziomu wieżyczki.
	void setFrameDimension(sf::Vector2i v);//ustawienie rozmiarów klatki na podane wartości.
	void refreshTextureRect();
	void refreshAnim();
	inline NewTargetMethod getTargetMethod(){return newTargetMethod;}//metoda zwracająca kogo ma namierzać dana wieżyczka.
	inline void setTargetMethod(NewTargetMethod v){newTargetMethod=v;}// metoda ustawiająca kogo ma namierzać dana wieżyczka.
	inline bool isMaxLevel(){return level>=TOWER_MAXLEVEL;}// metoda sprawdzająca czy wieżyczka jest na maksymalnym poziomie.
	inline int getBulletDelay()const{return newBulletDelay;}
	inline int getLevel()const{return level;}//metoda zwracająca poziom wieżyczki.
	inline int getMinDmg()const{return minDmg;}//metoda zwracająca minimalne obrażenia jakie wieżyczka może zadać.
	inline int getMaxDmg()const{return maxDmg;}//metoda zwracająca maksymalne obrażenia jakie wieżyczka może zadać.
	inline float getRange() const {return range;}// metoda zwracająca zasięg danej wieżyczki.
	inline sf::RectangleShape getSprite() const {return sprite;}// metoda zwraca sprite danej wieżyczki.
	inline Enemy* getTargetedEnemy() const {return targetedEnemy;}// metoda zwraca referencje aktualnie nacelowanego przeciwnika.
};

#endif /* TOWER_HPP_ */
