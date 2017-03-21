/*
 * AnimatedGround.cpp
 *
 *  Created on: 2016-05-10
 *      Author: jakub
 */

#include "AnimatedGround.hpp"
#include "Map.hpp"
#include <cmath>
AnimatedGround::AnimatedGround():
	extraFrames(6)
{
	for(size_t i=0; i<Conf::MAP_WIDTH*Conf::MAP_HEIGHT; ++i){
		frameVec.push_back(0);
	}

	setRowsAndCols(6,5);
	vtiles.setPrimitiveType(sf::Triangles);
}

int AnimatedGround::computeRealFrame(int currentFrame){
	if(currentFrame<0) return maxFrames-extraFrames-currentFrame-1;
	int fmod=0;
	if(currentFrame > maxFrames-extraFrames-1) fmod=(currentFrame-(maxFrames-extraFrames))*2+1;
	return currentFrame - fmod;
}
void AnimatedGround::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	states.texture=texture;
	target.draw(vtiles,states);
}
void AnimatedGround::updatePath(Path &p){
	std::vector<sf::Vector2i> v=p.getAsVector();

	Path::PathType now, last=p.getTypeAt(p.getStart());
	for(auto &e: v){
		now=p.getTypeAt(e);
		frameVec[e.x+e.y*Conf::MAP_WIDTH]=-last;
		last=now;
//		LOGE("%dx%d = %d",e.x,e.y,frameVec[e.x+e.y*Conf::MAP_WIDTH]);
	}
}
void AnimatedGround::updateVa(){
	LOGF("AnimatedGround::updateVa");

	sf::Vector2f p;
	size_t i=0;
	sf::Vertex v0,v1,v2,v5;

	sf::Vector2f siz=Conf::vw.getSize();
	sf::Vector2f ctr=Conf::vw.getCenter();
	sf::FloatRect fr;

	fr.left=ctr.x-siz.x/2;
	fr.top=ctr.y-siz.y/2;
	fr.width=siz.x;
	fr.height=siz.y;

	float tileHeight=(frameDimension.y*Conf::textureDivisor)/1.28;
	float heightDif=tileHeight-Conf::TILE_HEIGHT;

	vtiles.resize(0);

	sf::Vector2i start=Map::coords2XYABS(fr.left, fr.top);
	sf::Vector2i end=Map::coords2XYABS(fr.left+fr.width, fr.top+fr.height);
	start.x-=2;
	start.y-=1;

	end.x+=2;
	end.y+=2;

	for(int x=start.x; x<end.x; ++x){
		for(int y=start.y; y<end.y; ++y){
			p=Map::XY2Coords(x, y);

			p.y-=heightDif;
			v0.position=p;
			v1.position=p+sf::Vector2f(Conf::TILE_WIDTH,0.0f);
			v2.position=p+sf::Vector2f(Conf::TILE_WIDTH,tileHeight);
			v5.position=p+sf::Vector2f(0.0f,tileHeight);

			sf::IntRect ir;
			int cmod=0;

			if(x<0 || x>=Conf::MAP_WIDTH || y<0 || y>=Conf::MAP_HEIGHT){
				ir=getFrameRect(computeRealFrame(currentFrame));


				if(x<0) cmod+=-x*8;
				if(y<0) cmod+=-y*16;
				if(x>=Conf::MAP_WIDTH) cmod+=(1+(x-Conf::MAP_WIDTH))*8;
				if(y>=Conf::MAP_HEIGHT) cmod+=(1+(y-Conf::MAP_HEIGHT))*16;

			}else{
				int f=frameVec[x+y*Conf::MAP_WIDTH];
				if(f!=0){
					ir=getFrameRect(computeRealFrame(f));
				}else{
					ir=getFrameRect(computeRealFrame(currentFrame));
				}
			}

			v0.texCoords=sf::Vector2f(ir.left,ir.top);
			v1.texCoords=sf::Vector2f(ir.left+ir.width,ir.top);
			v2.texCoords=sf::Vector2f(ir.left+ir.width,ir.top+ir.height);
			v5.texCoords=sf::Vector2f(ir.left,ir.top+ir.height);

			srand(x+y*Conf::MAP_WIDTH);
			int c=235+rand()%20-cmod; CLMT(c);
			v0.color=sf::Color(c,c,c);
			c=235+rand()%20-cmod; CLMT(c);
			v1.color=sf::Color(c,c,c);
			c=235+rand()%20-cmod; CLMT(c);
			v2.color=sf::Color(c,c,c);
			c=235+rand()%20-cmod; CLMT(c);
			v5.color=sf::Color(c,c,c);

			vtiles.append(v0);
			vtiles.append(v1);
			vtiles.append(v2);
			vtiles.append(v0);
			vtiles.append(v2);
			vtiles.append(v5);
			i+=6;
		}
	}
	srand(time(NULL));
}
void AnimatedGround::update(){
	LOGF("AnimatedGround::update");

	float x=0.333*Conf::clock.getElapsedTime().asSeconds();
	delay=25.f + 50.f*(1+std::sin(x)*std::sin(0.667*x)*std::sin(1.572*x));

	if(Conf::clock.getElapsedTime().asMilliseconds() - lastTime >= delay){
		lastTime = Conf::clock.getElapsedTime().asMilliseconds();
		currentFrame=(currentFrame+1)%((maxFrames-extraFrames)*2);
	}
}
