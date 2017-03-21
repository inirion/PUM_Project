/*
 * Animation.cpp
 *
 *  Created on: 2 maj 2016
 *      Author: Piotr Okoń
 */

#include "Animation.hpp"

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(rect, states);
}
void Animation::update(){
	int diff=Conf::clock.getElapsedTime().asMilliseconds() - lastTime;
	if(diff >= delay){
		rect.setTextureRect(getFrameRect(currentFrame));
		currentFrame+=(diff/delay);
		if(currentFrame >= maxFrames){
			if(oneTime){
				currentFrame=maxFrames-1;
			}else{
				currentFrame = 0;
			}
		}
		lastTime = Conf::clock.getElapsedTime().asMilliseconds();
	}
}
sf::IntRect Animation::getFrameRect(int frame)const{
	return sf::IntRect(
			frame / rows * frameDimension.x,
			frame % rows * frameDimension.y,
			frameDimension.x,
			frameDimension.y
			);
}
void Animation::refreshTexture(){// odświeżenie tekstury(zainicjowanie jej nowymi danymi które mogły się zmienić)
	Textureable::setTexture(texName);
	rect.setTexture(texture);
	frameDimension.x = texture->getSize().x / cols;
	frameDimension.y = texture->getSize().y / rows;
}
void Animation::setTexture(std::string tex){
	texName = tex;
	refreshTexture();
}
