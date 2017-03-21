#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Lang.hpp"
#include "MenuView.hpp"
#include "Listener.hpp"
#include "S.hpp"

class MainMenu: public sf::Drawable{
private:
	std::map<std::string, MenuView> mvmap;
	MenuView *selected;
	sf::Vector2f firstPos;
	sf::Vector2f moveStep;
	sf::Vector2f miniStep;
	sf::Vector2f defBtnSiz;
	sf::Vector2f defCbSiz;
	sf::Vector2f bigBtnSiz;
	sf::Vector2f minBtnSiz;
	sf::Vector2f vzero;
	sf::Vector2f texS;
	sf::Vector2f moveRight;
	sf::Vector2f moveLeft;
	sf::Vector2f defTextShift;
	sf::Vector2f cbTextShift;
	int defFontSize;
	int bigFontSize;
	int minFontSize;
public:
	MainMenu();

	inline void resetGsLabel(){char gsbuf[16]; std::sprintf(gsbuf,"%.3f",Conf::gs); mvmap[S::menu_graphics].getButtonMap()[S::btn_gui_scale_label].setText(gsbuf);};//metoda resetująca game scale label;
	inline void resetMSoundLabel(){char msndbuf[16]; std::sprintf(msndbuf,"%.0f",Conf::menuSoundVolume); mvmap[S::menu_sound].getButtonMap()[S::btn_menu_sound_label].setText(msndbuf);}//metoda resetująca music sound label;
	inline void resetGSoundLabel(){char gsndbuf[16]; std::sprintf(gsndbuf,"%.0f",Conf::gameSoundVolume); mvmap[S::menu_sound].getButtonMap()[S::btn_game_sound_label].setText(gsndbuf);}//metoda resetująca game sound label;
	inline MenuView* getSelected(){return selected;}// metoda zwracająca wskaźnik aktualnego MenuView.
	inline void setSelected(std::string id){if(mvmap.find(id)!=mvmap.end()){selected=&mvmap.at(id);}else{selected=&mvmap[S::menu_empty];}}// metoda ustawiająca MenuViev na podany w parametrze.
	inline std::map<std::string, MenuView>& getMap(){return mvmap;}// metoda zwracająca referencję na mapę MenuView.
	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).

	inline void listenAllViews(Listener *l){ for(auto &mv: mvmap) mv.second.listenAllButtons(l); }// metoda nasłuchująca wszystkie View.
	inline void unlistenAllViews(Listener *l){ for(auto &mv: mvmap) mv.second.unlistenAllButtons(l);}//metoda kończąca nasłuchiwanie wszystkich View.
	inline void refreshAllViewsTexture(){for(auto &mv: mvmap) mv.second.refreshAllButtonsTexture();}// metoda odświeżająca wszystkie tekstury w MenuView.
};


#endif /* MAINMENU_HPP_ */
