#ifndef HAVEBUTTONS_HPP
#define HAVEBUTTONS_HPP

#include <map>
#include "SimpleButton.hpp"

class HaveButtons{
protected:
	std::map<std::string, SimpleButton> mbuttons;

public:
	inline void setButton(SimpleButton btn){btn.setName(btn.getText()); mbuttons[btn.getText()]=btn;}// setter ustawiający button na ten podany w parametrze uzupełniający mapę stringiem.
	inline void setButton(SimpleButton btn, std::string id){btn.setName(id); mbuttons[id]=btn;}// setter ustawiający button na ten podany w parametrze uzupełniający mapę wartością size_t.
	inline bool isClicked(std::string id){return mbuttons[id].isClicked();}// metoda sprawdzająca czy dany przyciska został kliknięty.
	inline bool isHover(std::string id){return mbuttons[id].isHover();}// metoda sprawdzająca czy użytkownik najechał na dany przycisk.
	inline std::map<std::string, SimpleButton> &getButtonMap(){return mbuttons;}// metoda zwracająca referencję na mapę przycisków.
	inline void listenAllButtons(Listener *l){for(auto &b:mbuttons) b.second.addListener(l); }// ustawienie nasłuchiwania na wszystkie przyciski.
	inline void unlistenAllButtons(Listener *l){for(auto &b: mbuttons) b.second.removeListener(l); }// wyłączenie nasłuchiwania na wszystkie przyciski.
	inline void refreshAllButtonsTexture(){// odświeżenie tekstur wszystkich przycisków.
		for(auto &b: mbuttons) {
			LOGD("Button::RefreshTexture name = %s parent = %s", b.second.getName().c_str(), b.second.getParent().c_str());
			b.second.refreshTexture();
			b.second.refreshImageTexture();
		}
	}
};

#endif
