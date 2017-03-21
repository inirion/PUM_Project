/*
 * Enemy.hpp
 *
 *  Created on: 25 kwi 2016
 *      Author: Grzegorz Kokoszka
 */

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Positionable.hpp"
#include "Textures.hpp"
#include "Conf.hpp"
#include "Path.hpp"
#include "log.hpp"
#include "Textable.hpp"
#include "Animation.hpp"
#include "FloatingDamage.hpp"
#include "Observable.hpp"
#include "Enabledable.hpp"
#include "S.hpp"


enum EnemyType {
	AIR, LAND, AIRANDLAND
};

#define ENEMYINTRECT sf::IntRect(0, 0, 64, 64)

class Enemy:
		public sf::Drawable,
		public Textable,
		public Enabledable,
		public Observable{
protected:
	static std::map<std::string, std::string> enemyPrices;
	static bool enemyPricesInited;

	Animation explodeSprite;
	Animation vehicleSprite;

	sf::Vector2f (*distortionFunc)(sf::Vector2f, float seed);
	EnemyType enemyType;
	std::vector<FloatingDamage> floatingDmg;
	bool flying;
	bool erase;
	bool exit;
	bool destroyed;
	int damage;
	int maxHP;
	int hp;
	int estimatedHP;
	float speed;
	float number;
	float lastFrameTime;
	float lastHitTime;
	float seed;

	Enemy(Path *path, bool f);

public:
	static void initPrices() {// metoda statyczna inicjalizująca wartości jakie dostanie gracz po zniszczeniu danego przeciwnika.
		if (!enemyPricesInited) {
			enemyPricesInited = true;

			enemyPrices["lighthovercraft"] = "20";
			enemyPrices["lightbomber"] = "30";
		}

	}
	static int priceOf(std::string t) {// metoda zwracająca cenę danego rodzaju przeciwnika po jego nazwie.
		if (enemyPrices.find(t) != enemyPrices.end()) {
			return std::stoi(enemyPrices.at(t));
		}
		return 0;
	}
	static std::string priceOfS(std::string t) {// metoda zwracająca stringa z ceną danego rodzaju przeciwnika po jego nazwie.
		if (enemyPrices.find(t) != enemyPrices.end()) {
			return enemyPrices.at(t);
		}
		return S::zero;
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	void update(std::vector<Vec3Enemy> &vec ,sf::Vector2f basePos);// metoda odświeżająca dany obiekt, pobiera ona wektor pozycji w jakich może znajdować się przeciwnik od miejsca startu do kolizji z bazą.
	void destroyAnim();// metoda wywołująca animacje zniszczenia danego przeciwnika.
	void revalidate();// metoda uaktualniająca pozycje danego przeciwnika.

	inline void setHP(int HP) {// setter ustawiający życie przeciwnika na daną wartość.
		hp = HP;
	}
	inline int getHP() const {// constowy getter zwracający życie danego przeciwnika w danej chwili.
		return hp;
	}
	void hit(int HP);// metoda dodająca obrażenia do wektora floating dmg oraz odejmująca życie przeciwnikowi.
//	inline void setDestroyed(bool d) {
//		destroyed = d;
//	}
	void destroyIt();// metoda inicjalizująca animacje zniszczenia danego przeciwnika.
	inline bool getErase() {// getter zwracający czy dany przeciwnik został zniszczony czy nie.
		return erase;
	}
	inline void setEstimatedHP(int HP) {// setter ustawiający życie przeciwnika na podane w parametrze.
		estimatedHP = HP;
	}
	inline int getEstimatedHP() const {// constowy getter zwracający oczekiwane życie przeciwnika.
		return estimatedHP;
	}
	inline int getDamage() const {// constowy getter zwracający obrażenia jakie otrzymał przeciwnik.
		return damage;
	}
	inline EnemyType getType() const {// getter zwracający rodzaj przeciwnika(ziemny,powietrzny,ziemno-powietrzny).
		return enemyType;
	}
	inline bool isFlying() const { return flying; }// metoda boolowska ukazująca czy przeciwnik jest jednostką napowietrzną.
	static inline sf::Vector2f defDistort(sf::Vector2f pos, float seed) {// metoda zwracająca niepewność ruchu danego przeciwnika jest ona implementowana w rodzajach przeciwników(referencja na funkcję), zwraca ona pozycję w jakiej znajduję się przeciwnik po przeliczonych odchyleniach sprawia to że przeciwnik zaczyna oscylować wokół drogi zamiast jechać na niej prostymi liniami.
		return pos;
	}
	virtual void refreshTexture();//metoda odświeżająca teksturę.
	inline Animation getAnim()const{return vehicleSprite;}
};

#endif /* ENEMY_HPP_ */
