#include "MenuView.hpp"
void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	for(const auto &button : mbuttons){
		target.draw(button.second,states);
	}
}

void MenuView::update(sf::RenderWindow &rw){
	for(auto &button : mbuttons){
			button.second.update(rw);
	}
}


