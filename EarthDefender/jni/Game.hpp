#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#include "Textures.hpp"
#include "Conf.hpp"
#include "MainMenu.hpp"
#include "Map.hpp"
#include "Path.hpp"
#include "PanelManager.hpp"
#include "Listener.hpp"
#include "S.hpp"

#define RESETMYGS() Conf::gs = std::sqrt(Conf::dWidth * Conf::dHeight) / 1024;

class Game : public Listener{
private:
	sf::RenderWindow &rw;
	sf::RectangleShape sBackground;
	MainMenu mainMenu;
	Map map;
	PanelManager panelManager;
	sf::Text debugText;
	sf::Thread initThread;
//	sf::Vector2i pos;

	bool dirty;
	bool loading;
	bool baseDestroy;
	bool backgroundEnable;
	int money;
	int enemyCount;
	int loadedEnemies;
	int enemiesKilled;
	int baseMaxHP;
	int baseHP;
	float time;
	float startBaseDestroyTime;
	float debugTextTime;
	int currentWave, maxWaves;

	void drawStatusBar();
	void destroyBase();
	void initGame();
	void drawShadow(sf::Text &t, float shift, sf::Color c1, sf::Color c2);
public:

	Game(sf::View &view, sf::RenderWindow &win); //Domyślny konstruktor
	~Game(){}
	void terminateThread(){initThread.terminate();}// metoda zatrzymująca wątek.
	void events();// metoda wywołująca updaty klas zawartych w tej klasie
	void drawDebugInfo();// metoda wypisująca paratemtry potrzebne przy debugowaniu takie jak dtime , fps, aktualna scena itp.
	void backgroundDraw();// metoda malująca tło.
	void drawMenu();//metoda wywołująca metodę draw z kalsy MainMenu.
	void gameDraw();// metoda malująca grę oraz panel informacji o graczu.
	void review();// metoda ustawiająca widok na ten ustawiony w klasie konfiguracyjnej
	void cameraCheck();// metoda sprawdzająca czy dany obszar znajduję się w obrębie widzialnego, ustawiająca aktualne centrum widoku w klasie konfiguracyjnej.
	void dirtyCheck();
	virtual void notify(ListenerMessage &msg);// metoda powiadamiająca klasy które aktualnie nasłuchują o zmianach.
	void moneyHandle();// metoda sprawdzająca czy mamy wymaganą ilość pieniędzy na operacje z nią związaną.
	void towerPanelHandle();//metoda uaktualniająca wartości przy operacji na wieżyczkach.
	void targetPanelHandle();// metoda opisująca zachowanie wieżyczek względem przeciwników(kolejność celowania w przeciwników : pierwszy, najbliższy lub ostatni).
	void drawLoadingScreen();// metoda rysująca pasek ładowania.
	void backgroundResize();// metoda zmieniająca wymiary tła. Zgodnie z rozmiarem ekranu

};

#endif /* GAME_HPP_ */
