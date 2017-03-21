#include "Conf.hpp"
#include "Gestures.hpp"
#include "log.hpp"

Gestures::GestureAction Gestures::gestureAction=Gestures::NoAction;
bool Gestures::holding[2];
float Gestures::holdStartTime=0.0f;
sf::Vector2f Gestures::holdPoint[2];
sf::Vector2i Gestures::holdPointI[2];
sf::Vector2f Gestures::slideSpeed;
int Gestures::pinchVal=0;
bool Gestures::locked=false;

void Gestures::update(sf::RenderWindow &rw){
	LOGF("Gestures::update");

	if(!Conf::windowFocused) return;

	locked=false;

	if(!holding[0]){
		gestureAction=NoAction;
		if(SFISPOINTERDOWN(0)){
			holdPointI[0]=SFGETPOINTERPOSITION(0);
			holdPoint[0]=rw.mapPixelToCoords(holdPointI[0]);
			holding[0]=true;
			holdStartTime=Conf::clock.getElapsedTime().asSeconds();
		}
		if(sf::Touch::isDown(1)){
			holdPointI[1]=sf::Touch::getPosition(1,rw);
			holdPoint[1]=rw.mapPixelToCoords(holdPointI[1]);
			holding[1]=true;
		}
	}else{
		if(!SFISPOINTERDOWN(0)){
			holding[0]=false;
			if(Conf::clock.getElapsedTime().asSeconds() - holdStartTime < 0.450 && std::fabs(slideSpeed.x)+std::fabs(slideSpeed.y) < 80*Conf::zm){
				gestureAction=FastTap;
			}
		}else{
			if(!sf::Touch::isDown(1)){
				if(!holding[1]){
					gestureAction=Slide;
					sf::Vector2f p=rw.mapPixelToCoords(SFGETPOINTERPOSITION(0));

					slideSpeed=holdPoint[0]-p;

					if(std::fabs(slideSpeed.x)+std::fabs(slideSpeed.y) < 4*Conf::zm){
						gestureAction=Hold;
					}
				}else{
					holdPointI[0]=SFGETPOINTERPOSITION(0);
					holdPoint[0]=rw.mapPixelToCoords(holdPointI[0]);
				}

				holding[1]=false;
			}else{
				if(holding[1]){
					gestureAction=Pinch;

					sf::Vector2i diff;
					diff=holdPointI[0]-holdPointI[1];
					int oldD=std::sqrt(diff.x*diff.x+diff.y*diff.y);
					holdPointI[0]=(sf::Touch::getPosition(0,rw));
					holdPointI[1]=(sf::Touch::getPosition(1,rw));
					diff=holdPointI[0]-holdPointI[1];
					int thisD=std::sqrt(diff.x*diff.x+diff.y*diff.y);
					pinchVal=oldD - thisD;
				}else{
					holdPointI[0]=(sf::Touch::getPosition(0,rw));
					holdPointI[1]=(sf::Touch::getPosition(1,rw));
					holding[1]=true;
				}
			}
		}
	}
}
