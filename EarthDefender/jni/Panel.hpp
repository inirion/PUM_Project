#ifndef PANEL_HPP_
#define PANEL_HPP_

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Lang.hpp"
#include "Conf.hpp"
#include "Gestures.hpp"
#include "HaveButtons.hpp"
#include "Textable.hpp"
#include "PosReferenceable.hpp"
#include "Textureable.hpp"
#include "Hoverable.hpp"

class Panel:
		public sf::Drawable,
		public Hoverable,
		public Textable,
		public PosReferenceable,
		public Textureable,
		public HaveButtons {

private:
	SimpleButton special;
	float openValue;
	bool opening;

	float scroll;
	float scrollVelocity;
	float scrollStop;

public:
	Panel(std::string nameid = "") :
			Textable(nameid, 32), Textureable("color.dgray"), openValue(0.0), opening(
					false), scroll(0.0f), scrollVelocity(0.0f), scrollStop(0.0f) {
		hpr = hprRight;
		textCenter = true;
		textShift.x = 0.f;
		textShift.y = 20.f;

		size.x = 200.0f;
		size.y = 200.0f;
	}

	inline void setScrollStop(float s) {
		scrollStop = s;
	}
	inline void close() {
		openValue -= 0.1 * Conf::dtime;
		opening = false;
	}
	inline void open() {
		opening = true;
	}
	inline bool isOpened() {
		return openValue >= 1.0;
	}
	inline void setSpecialButton(SimpleButton &btn) {
		special = btn;
	}
	inline SimpleButton &getSpecialButton() {
		return special;
	}

	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
};

#endif /* PANEL_HPP_ */
