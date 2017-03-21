#include "Conf.hpp"

float Conf::zm=1.0f;
float Conf::gs=1.0f;

float Conf::newzoom=1.0f;

int Conf::dHeight=800;
int Conf::dWidth=480;

sf::Vector2f Conf::hoverPos;

sf::Font Conf::fSansation;
sf::Font Conf::fMono;
sf::Clock Conf::clock;
sf::Clock Conf::FPSclock;
float Conf::dtime = 0.0f;

bool Conf::inited = false;
bool Conf::gameRun = false;
bool Conf::gamePause = true;
bool Conf::debugEnable = true;
bool Conf::windowFocused = false;

float Conf::menuSoundVolume=100.0f;
float Conf::gameSoundVolume=100.0f;

//float Conf::TILE_WIDTH = 200;
//float Conf::TILE_HEIGHT = 100;
//int Conf::MAP_WIDTH = 24;
//int Conf::MAP_HEIGHT = 12;

int Conf::textureDivisor = 1;

sf::View Conf::vw;
sf::Mutex Conf::rwmutex;

void Conf::init(){
	if(!inited){
		inited=true;
		fSansation.loadFromFile("font/sansation.ttf");
		fMono.loadFromFile("font/DroidSansMono.ttf");

	}
}
sf::IntRect Conf::irCorrection(sf::IntRect ir){
	ir.width/=Conf::textureDivisor;
	ir.height/=Conf::textureDivisor;
	ir.top/=Conf::textureDivisor;
	ir.left/=Conf::textureDivisor;
	return ir;
}
sf::IntRect Conf::irCorrection(sf::Vector2i fd){
	return irCorrection(sf::IntRect(0,0,fd.x,fd.y));
}

