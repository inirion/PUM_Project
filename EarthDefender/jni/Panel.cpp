#include "Panel.hpp"

void Panel::update(sf::RenderWindow &rw) {
	if (opening) {
		openValue += std::sqrt(-(openValue - 1.0f)) * 10 * Conf::dtime;

		if (openValue >= 1.0f) {
			opening = false;
			openValue = 1.0f;
		}
	} else if (openValue > 0.0f && openValue < 1.0f) {
		openValue -= std::sqrt(-(openValue - 1.0f)) * 10 * Conf::dtime;

		if (openValue <= 0.0f) {
			scroll = 0.f;
			openValue = 0.0f;
		}
	}

	if (std::fabs(scrollVelocity) > 0.001) {
		scroll += (scrollVelocity * Conf::dtime * Conf::gs) / Conf::zm;
		scrollVelocity -= scrollVelocity * 10 * Conf::dtime;

		if (scroll < 0.0f)
			scroll = 0.0f;
		if (scroll > scrollStop)
			scroll = scrollStop;
	}

	if (openValue != 0.0f) {
		sf::FloatRect fr;
		fr.width = size.x * Conf::gs * Conf::zm;
		fr.height = size.y * Conf::gs * Conf::zm;

		sf::Vector2f computed = computedPosition(rw, size);
		fr.left = computed.x;
		fr.top = computed.y;

		if (hpr == hprRight) {
			fr.left += fr.width * (-(openValue - 1.0f));
		} else if (hpr == hprLeft) {
			fr.left += fr.width * (openValue - 1.0f);
		}

		special.setRefRectangle(fr);
		fr.top -= scroll * Conf::zm * Conf::gs;

		if(Conf::gamePause){
			for (auto &b : mbuttons) {
				b.second.setRefRectangle(fr);
			}
		}else{
			special.update(rw);
			for (auto &b : mbuttons) {
				b.second.setRefRectangle(fr);
				b.second.update(rw);
			}
		}
	}

	if( openValue >= 0.9f) {
		checkHover(rw, computedPosition(rw, size));
		if (Conf::clock.getElapsedTime().asSeconds() - hoverTime < 0.1) {
			scrollVelocity += Gestures::getSlideSpeed().y;
			Gestures::lock();
		}
	}
}
void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (openValue > 0.0f) {
		sf::RectangleShape s;
		sf::Text t(l(text), Conf::fSansation, textSize * Conf::gs);

		sf::Vector2f rsiz;
		rsiz=size * Conf::gs;
		rsiz.y=target.getSize().y;

		s.setSize(rsiz);
		s.setTexture(texture);
		s.setOutlineColor(sf::Color::Transparent);
		s.setFillColor(sf::Color(255, 255, 255, 200));
		s.setOutlineThickness(0.0f);
		s.setScale(Conf::zm, Conf::zm);

		rsiz.x=size.x;
		sf::Vector2f computed = computedPosition(target, rsiz);
		s.setPosition(computed);

		if (vpr == vprTop) {

		} else if (vpr == vprBottom) {

		}

		if (hpr == hprRight) {
			s.move(s.getGlobalBounds().width * (-(openValue - 1.0f)), 0.0f);
		} else if (hpr == hprLeft) {
			s.move(s.getGlobalBounds().width * (openValue - 1.0f), 0.0f);
		}

		t.setPosition(s.getPosition() + textShift * Conf::gs * Conf::zm);
		t.setScale(Conf::zm, Conf::zm);

		if (textCenter) {
			t.move((s.getGlobalBounds().width - t.getGlobalBounds().width) / 2,
					0.0f);
		}

		target.draw(s, states);
		for (const auto &b : mbuttons) {
			target.draw(b.second, states);
		}

		sf::Text test = t;
		test.setString("A");
		s.setSize(sf::Vector2f(size.x * Conf::gs, (test.getGlobalBounds().height * 3 / Conf::zm)));
		target.draw(s, states);
		target.draw(t, states);
		target.draw(special);
	}
}
