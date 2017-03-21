#ifndef PANELMANAGER_HPP_
#define PANELMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Panel.hpp"
#include "S.hpp"

class PanelManager : public sf::Drawable{
private:
	std::map<std::string, Panel> mpanels;

	sf::Vector2f vzero;
	sf::Vector2f moveStep;
	sf::Vector2f moveRight;

public:
	PanelManager();
	inline std::map<std::string, Panel>& getMap(){return mpanels;}// metoda zwracająca referencje na mapę Paneli.
	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	void refreshAllPanelsTexture();//metoda odświeżająca wszystkie tekstury paneli.

	inline void listenAllPanels(Listener *l){ for(auto &mv: mpanels){mv.second.listenAllButtons(l); mv.second.getSpecialButton().addListener(l); }}//metoda powodująca nasłuchiwanie wszystkich obiektów w mapie mpanels.
	inline void unlistenAllPanels(Listener *l){ for(auto &mv: mpanels){mv.second.unlistenAllButtons(l); mv.second.getSpecialButton().removeListener(l); }}//metoda powodująca zakończenie nasłuchiwanie wszystkich obiektów w mapie mpanels.
	inline void closeAll(){ for(auto &mv: mpanels) mv.second.close();}
	inline void close(std::string id){if(mpanels.find(id)!=mpanels.end()) mpanels[id].close();}
	inline void open(std::string id){if(mpanels.find(id)!=mpanels.end()) mpanels[id].open();}
};


#endif /* PANELMANAGER_HPP_ */
