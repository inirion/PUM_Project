/*
 * Grass.cpp
 *
 *  Created on: 2 maj 2016
 *      Author: Grzegorz Kokoszka
 */

#include "Grass.hpp"
#include "Map.hpp"

void Grass::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(grass, states);
}

void Grass::update() {
	float x = 0.333 * Conf::clock.getElapsedTime().asSeconds();
	frameDelay = 25.f + 50.f * (1 + sin(x) * sin(0.667 * x) * sin(1.572 * x));

	if (Conf::clock.getElapsedTime().asMilliseconds() - lastFrameTime
			>= frameDelay) {
		if (Conf::debugEnable) {
			sf::Text coordText(
					std::to_string(xyPosition.x) + ","
							+ std::to_string(xyPosition.y), Conf::fMono, 32);
			coordText.setPosition(
					position.x + Conf::TILE_WIDTH / 2
							- coordText.getLocalBounds().width / 2,
					position.y + Conf::TILE_HEIGHT + 30
							- coordText.getLocalBounds().height / 2);
			coordText.setFillColor(sf::Color(0, 0, 0, 192));
			Text = coordText;
		}
		currentFrame = (currentFrame + 1) % frame_count;

		int fmod = 0;
		if (currentFrame > frame_count / 2 - 1) {
			fmod = (currentFrame - (frame_count / 2)) * 2 + 1;
		}
		sf::Vector2i v((currentFrame - fmod) / 6 * frameDimension.x,
				(currentFrame - fmod) % 6 * frameDimension.y);

		grass.setTextureRect(
				sf::IntRect(v.x, v.y, frameDimension.x, frameDimension.y));
		lastFrameTime = Conf::clock.getElapsedTime().asMilliseconds();
	}
}

