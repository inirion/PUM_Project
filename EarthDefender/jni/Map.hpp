/*
 * Map.hpp
 *
 *  Created on: 20 kwi 2016
 *      Author: Piotr Okoń
 */
#ifndef MAP_HPP_
#define MAP_HPP_
#include <SFML/Graphics.hpp>
#include "log.hpp"
#include "Textures.hpp"
#include "Path.hpp"
#include "Tower.hpp"
#include "Gestures.hpp"
#include "Enemy.hpp"
#include "Observable.hpp"
#include "Listener.hpp"
#include "GroundShadow.hpp"
#include "Grass.hpp"
#include "Base.hpp"
#include "AnimatedGround.hpp"

struct Vector2iCmp{
    bool operator()( sf::Vector2i const& l, sf::Vector2i const& r ) const
    {
    	if(l.x != r.x){
    		return l.x < r.x;
    	}else{
    		return l.y < r.y;
    	}
    }
};

class Map:
//	public Positionable,
	public sf::Drawable,
	public Observable,
	public Listener
{
private:
	Path path;
//	sf::RectangleShape sprite;
	sf::Vector2i selected;
	std::vector<Tower*> towers;
	std::vector<Enemy*> enemies;
	sf::FloatRect visibleBounds;
	Base base;
//	GroundShadow groundShadow;
	AnimatedGround animatedGround;
	bool visibleBoundsInit;

	float lastEnemyTime;
	size_t killedEnemiesCounter;
	size_t lastNonActivatedEnemy;
	size_t spawnedEnemies;
	size_t fpsLimit;
//	std::vector<std::vector<sf::Drawable*>> drawVec;
	std::map<sf::Vector2i, std::vector<sf::Drawable*>, Vector2iCmp> drawVec;
	std::vector<float> spawnTime;

	void drawTowerRadius(sf::RenderTarget &target) const;
	void drawSelectedTile(sf::RenderTarget &target) const;
	void drawDrawVec(sf::RenderTarget &target) const;
	void updateTowers(sf::RenderWindow &rw);
	void updateEnemies(sf::RenderWindow &rw);
	void updateIsometricMap();
	inline bool isInVisibleBounds(sf::Vector2f pos) const;
	bool isTowerOnTile(sf::Vector2i i) const;

public:
	Map();
	virtual ~Map(){}
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	static sf::Vector2f XY2Coords(int x, int y);// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	static sf::Vector2i coords2XY(float x, float y);// metoda przetwarzająca współrzędne podane jako argument na koordynaty na mapie.
	static sf::Vector2i coords2XYABS(float x, float y);// metoda przetwarzająca współrzędne podane jako argument na koordynaty na mapie(bardziej dokładna).
	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	void zoom(int delta);//metoda ustawiająca nowe wartości zmiennej zoom w klasie konfiguracyjnej.
	void cameraCheck(sf::RenderWindow &rw);
	virtual void notify(ListenerMessage &msg);// metoda informująca o zmianach wszystkie klasy jakie słuchają.
	Tower* getSelectedTower();// metoda zwracająca referencje na wybraną wieżyczkę.
	inline Base& getBase() {// metoda zwracająca referencje na bazę.
		return base;
	}
	void spawningInit(size_t i);//metoda inicjalizująca wektor spawntime wartościami(kontrola wielkości fal przeciwników).
	inline int enemiesKilled(){return killedEnemiesCounter;}//metoda zwracająca ilość zniszczonych przeciwników.
	inline void setEnemies(std::vector<Enemy*> &v) {//inicjalizacja zmiennej enemies wartością podaną jako argument.
		enemies = v;
	}
	inline Path& getPath() {// metoda zwracająca referencje na obiekt klasy Path.
		return path;
	}
	void refreshAllTextures();//metoda odświeżająca tekstury wszystkich przeciwników.
	void updateVisibleBounds(sf::RenderWindow &rw);// metoda wyznaczająca widzialne krawędzie gry.
	inline void nextWave() { if (lastNonActivatedEnemy < spawnTime.size() - 1) spawnTime[lastNonActivatedEnemy] = 0.f; }//metoda określająca przerwę między pojawianiem się fal przeciwników.
};

#endif /* MAP_HPP_ */
