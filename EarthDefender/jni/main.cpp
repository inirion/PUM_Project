#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "log.hpp"
#include "Game.hpp"
#include "Textures.hpp"
#include "Conf.hpp"
#include "Lang.hpp"
#include "SfEventBridge.hpp"


int main(int argc, char *argv[]){
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Earth Defender");
	window.setVerticalSyncEnabled(true);
	sf::View view = window.getDefaultView();

	Conf::windowFocused=true;
	Conf::dHeight = view.getSize().y;
	Conf::dWidth = view.getSize().x;

	if(Conf::dHeight > Conf::dWidth){
		Conf::dHeight += Conf::dWidth;
		Conf::dWidth = Conf::dHeight - Conf::dWidth;
		Conf::dHeight -= Conf::dWidth;
	}
	RESETMYGS();

	sf::Texture *text = new sf::Texture();
	text->loadFromFile("img/background.png");
	text->setSmooth(true);


	sf::RectangleShape bg;
	bg.setTexture(text);
	bg.setPosition(0,0);
	bg.setSize(sf::Vector2f(Conf::dWidth, Conf::dHeight));
	window.draw(bg);
	window.display();
	delete text;

	Lang::init();
	Conf::init();
	Textures::init();
	Sounds::init();
	Enemy::initPrices();
	Tower::initPrices();

	Game g(view,window);
	SfEventBridge bridge;
	bridge.addListener(&g);

	std::size_t counter=0;
	while (window.isOpen()){
		++counter;

		Conf::dtime = Conf::FPSclock.getElapsedTime().asSeconds();
		Conf::FPSclock.restart();

		window.clear(sf::Color::Blue);

		g.events();

		sf::Event event;

		while (window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:{
					bridge.sendMessage(S::cmd_closeapp,S::one);
					window.close();
				}break;

				case sf::Event::Resized:{
					bridge.sendMessage(S::cmd_resized,S::one);
				}break;

				case sf::Event::GainedFocus:{
					Conf::windowFocused=true;
				}break;

				case sf::Event::LostFocus:{
					Conf::windowFocused=false;
					bridge.sendMessage(S::cmd_showmenu,S::one);
				}break;

				case sf::Event::KeyPressed:{
					std::string key=std::to_string(event.key.code);

					switch(event.key.code){
						case sf::Keyboard::Escape:{
							if(!Conf::gamePause){
								bridge.sendMessage(S::cmd_showmenu,S::one);
							}else{
								bridge.sendMessage(S::cmd_menuback,S::one);
							}
						}break;

						default: break;
					}
				}break;

				default: break;
			}
		}
		g.backgroundDraw();
		g.gameDraw();
		g.drawMenu();
		g.drawDebugInfo();

		g.dirtyCheck();
		window.display();
	}
	g.terminateThread();
	//tu powinno się coś synchronizować, np opcje do pliku na karcie sd

	return 0;
}
