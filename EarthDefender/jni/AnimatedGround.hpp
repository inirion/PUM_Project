/*
 * AnimatedGround.hpp
 *
 *  Created on: 2016-05-10
 *      Author: jakub
 */

#ifndef ANIMATEDGROUND_HPP_
#define ANIMATEDGROUND_HPP_

#include <map>
#include "Grass.hpp"
#include "Animation.hpp"
#include "Path.hpp"

class AnimatedGround : public Animation{
private:
	sf::VertexArray vtiles;
	std::vector<int> frameVec;
	int extraFrames;

	int computeRealFrame(int currentFrame);
public:
	AnimatedGround();
	virtual ~AnimatedGround(){}
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	virtual void update(); // metoda odświeżająca dany obiekt.
	void updateVa();// metoda odświeżająca Vertex nadająca mu różne kolory powodująca ładną iluzje optyczną.
	void updatePath(Path &p);// metoda odpowiadająca za animowanie trawy w pobliżu drogi.
};

#endif /* ANIMATEDGROUND_HPP_ */
