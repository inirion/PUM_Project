#ifndef CONF_HPP_
#define CONF_HPP_
#include <SFML/Graphics.hpp>

#define RUNFPSLIMIT 60
#define PAUSEFPSLIMIT 15

class Conf{ //statyczna klasa globalnej konfiguracji - wszystkie elementy powinny mieć tu dostęp

public:
	static float zm;	//zoom
	static float gs;	//gui scale

	static float newzoom;

	static int dHeight;
	static int dWidth;
	static const int TILE_WIDTH=200;
	static const int TILE_HEIGHT=100;

	static const int MAP_WIDTH=24;
	static const int MAP_HEIGHT=12;

	static sf::Font fSansation;
	static sf::Font fMono;
	static sf::Clock clock;
	static sf::Clock FPSclock;
	static float dtime;

	static sf::Vector2f hoverPos;

	static bool gameRun;
	static bool gamePause;

	static float menuSoundVolume;
	static float gameSoundVolume;

	static sf::View vw;

	static bool debugEnable;
	static bool windowFocused;

	static sf::Mutex rwmutex;
	static int textureDivisor;

	static bool inited;
	static void init();

	static sf::IntRect irCorrection(sf::IntRect ir);
	static sf::IntRect irCorrection(sf::Vector2i fd);
};

#define ISCLICKED(n) msg.objectname == n && msg.changes["clicked"]=="1"

#define CLOCKASSEC Conf::clock.getElapsedTime().asSeconds()
#define CLOCKASMS Conf::clock.getElapsedTime().asMilliseconds()

#define CLMT(n) if(n > 255) n=255; else if(n < 0) n=0;


#endif /* CONF_HPP_ */

