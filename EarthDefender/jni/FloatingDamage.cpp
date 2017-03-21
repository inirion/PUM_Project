#include "FloatingDamage.hpp"

#include "log.hpp"

void FloatingDamage::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(text, states);
}
void FloatingDamage::update(sf::Vector2f pos){
	int diff = CLOCKASMS - lastTime;
	if (diff >= delay) {
		position = pos;
		deltaY += (diff * 2.f) / delay;
		position.y -= deltaY;
		if (enemyFlying) position.y -= 78;
		position.x += deltaX;

		text.setPosition(position);
		int transparent = 255 - (deltaY * 2);
		if (transparent < 0) {
			transparent = 0;
			toDel = true;
		}
		text.setFillColor(sf::Color(255, 255, 255, transparent));
		if (scaling) {
			float sin = 1.f + std::sin((CLOCKASSEC - startTime) *4.f);
			if (sin < 1) {
				sin = 1;
				scaling = false;
			}
			text.setScale(sin, sin);
		}
//		LOGE("FD UPDATE %d", CLOCKASMS - lastTime);
		lastTime = CLOCKASMS;
	}
}
void FloatingDamage::increaseDmg(int dmg){
	damageAmount += dmg;
	++hits;
	std::string s = std::to_string(damageAmount)+" ("+std::to_string(hits)+" hits)";
	text.setString(s);
}
