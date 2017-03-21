#include "GroundShadow.hpp"
#include "Textures.hpp"
#include "log.hpp"

void GroundShadow::generate(size_t seed, sf::FloatRect rect, brushMode brush, float minRadius, float maxRadius, unsigned char minTransparent, unsigned char maxTransparent,  size_t iter){
	va.clear();
	va.resize(6*iter);
	va.setPrimitiveType(sf::Triangles);

	srand(seed);

	if(minRadius > maxRadius){
		float tmp=minRadius;
		minRadius=maxRadius;
		maxRadius=tmp;
	}
	if(minTransparent > maxTransparent){
		unsigned char tmp=minTransparent;
		minTransparent=maxTransparent;
		maxTransparent=tmp;
	}

	switch(brush){
		case soft: texture=&Textures::get("brush.soft"); break;
		case medium: texture=&Textures::get("brush.medium"); break;
		case hard: texture=&Textures::get("brush.hard"); break;
	}

	int los;

	for(size_t i=0; i<va.getVertexCount(); i+=6){
		los=rand()%10000;
		float diffr=maxRadius-minRadius;
		float r=minRadius + diffr * los/10000.0f;

		los=rand()%10000;
		sf::Vector2f p;
		p.x=rect.left + rect.width * los/10000.0f;
		los=rand()%10000;
		p.y=rect.top + rect.height * los/10000.0f;


		los=rand()%100;
		unsigned char trans=minTransparent + (maxTransparent-minTransparent) * los/100.f;

		va[i+0].color=sf::Color(255,255,255,trans);
		va[i+1].color=sf::Color(255,255,255,trans);
		va[i+2].color=sf::Color(255,255,255,trans);
		va[i+3].color=va[i+2].color;
		va[i+4].color=va[i+1].color;
		va[i+5].color=sf::Color(255,255,255,trans);

		va[i+0].position.x=p.x - r;
		va[i+0].position.y=p.y - r/2;
		va[i+1].position.x=p.x + r;
		va[i+1].position.y=p.y - r/2;
		va[i+2].position.x=p.x - r;
		va[i+2].position.y=p.y + r/2;
		va[i+3].position=va[i+2].position;
		va[i+4].position=va[i+1].position;
		va[i+5].position.x=p.x + r;
		va[i+5].position.y=p.y + r/2;

		va[i+0].texCoords.x=0;
		va[i+0].texCoords.y=0;
		va[i+1].texCoords.x=256;
		va[i+1].texCoords.y=0;
		va[i+2].texCoords.x=0;
		va[i+2].texCoords.y=256;
		va[i+3].texCoords=va[i+2].texCoords;
		va[i+4].texCoords=va[i+1].texCoords;
		va[i+5].texCoords.x=256;
		va[i+5].texCoords.y=256;
	}
}

void GroundShadow::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	states.texture=texture;
	target.draw(va,states);
}
