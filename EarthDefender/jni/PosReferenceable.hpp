#ifndef POSREFERENCEABLE_HPP_
#define POSREFERENCEABLE_HPP_

#include "Positionable.hpp"

enum VpositionReference{
	vprTop,
	vprBottom,
	vprCenter
};
enum HpositionReference{
	hprLeft,
	hprRight,
	hprCenter
};

class PosReferenceable: public Positionable{
protected:
	HpositionReference hpr;
	VpositionReference vpr;
	bool absolutePosition;
	bool percentPosition;
	bool screenReference;
	sf::FloatRect refRectangle;

public:
	PosReferenceable(HpositionReference h=hprCenter, VpositionReference v=vprCenter):
		hpr(h),
		vpr(v),
		absolutePosition(false),
		percentPosition(true),
		screenReference(true)
	{

	}

	inline void setScreenReference(bool val){screenReference=val;}
	inline void setRefRectangle(sf::FloatRect &fr){refRectangle=fr;}
	inline void setPositionReference(VpositionReference v, HpositionReference h){hpr=h; vpr=v;}
	inline void setPercentPosition(bool val){percentPosition=val;}

	sf::Vector2f computedPosition(sf::RenderTarget &rw, sf::Vector2f size)const{
		sf::Vector2f cmp;

		if(absolutePosition){
			cmp=position;
		}else{
			sf::Vector2f hook;

			if(screenReference){

				if(hpr == hprCenter) hook.x=rw.getView().getCenter().x;
				else if(hpr == hprLeft) hook.x=rw.mapPixelToCoords(sf::Vector2i(0,0)).x;
				else if(hpr == hprRight) hook.x=rw.mapPixelToCoords(sf::Vector2i(Conf::dWidth,0)).x;

				if(vpr == vprCenter) hook.y=rw.getView().getCenter().y;
				else if(vpr == vprTop) hook.y=rw.mapPixelToCoords(sf::Vector2i(0,0)).y;
				else if(vpr == vprBottom) hook.y=rw.mapPixelToCoords(sf::Vector2i(0,Conf::dHeight)).y;

				if(percentPosition){
					cmp=(hook+sf::Vector2f(position.x*Conf::dWidth*Conf::zm, position.y*Conf::dHeight*Conf::zm));
				}else{
					cmp=(hook+position*Conf::zm*Conf::gs);
				}
			}else{
				if(hpr == hprCenter) hook.x=refRectangle.left+refRectangle.width/2;
				else if(hpr == hprLeft) hook.x=refRectangle.left;
				else if(hpr == hprRight) hook.x=refRectangle.left+refRectangle.width;

				if(vpr == vprCenter) hook.y=refRectangle.top+refRectangle.height/2;
				else if(vpr == vprTop) hook.y=refRectangle.top;
				else if(vpr == vprBottom) hook.y=refRectangle.top+refRectangle.height;

				if(percentPosition){
					cmp=(hook+sf::Vector2f(position.x*refRectangle.width, position.y*refRectangle.height));
				}else{
					cmp=(hook+position*Conf::zm*Conf::gs);
				}

			}

			if(vpr == vprCenter) cmp.y-=size.y*Conf::zm*Conf::gs/2;
			if(vpr == vprBottom) cmp.y-=size.y*Conf::zm*Conf::gs;

			if(hpr == hprCenter) cmp.x-=size.x*Conf::zm*Conf::gs/2;
			if(hpr == hprRight) cmp.x-=size.x*Conf::zm*Conf::gs;
		}

		return cmp;
	}
};


#endif /* POSREFERENCEABLE_HPP_ */
