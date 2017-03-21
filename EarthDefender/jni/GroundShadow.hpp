#ifndef GROUNDSHADOW_HPP_
#define GROUNDSHADOW_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Conf.hpp"

class GroundShadow : public sf::Drawable{
private:
	sf::VertexArray va;
	sf::Texture *texture;

public:
	enum brushMode{
		soft=1,
		medium=2,
		hard=4
	};


	GroundShadow():
		texture(NULL)
	{}

	void generate(size_t seed, sf::FloatRect rect, brushMode brushes, float minRadius, float maxRadius, unsigned char minTransparent, unsigned char maxTransparent,  size_t iter);//metoda generująca przyciemnienie podłoża
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
};

#endif /* GROUNDSHADOW_HPP_ */
