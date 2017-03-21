#include "Path.hpp"
#include "Map.hpp"

void Path::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.texture = texture;
	target.draw(va, states);
}
void Path::initVec3Enemy(){
	bool exit=false;
	int iteratorVec3Enemy=0;

	sf::Vector2f temp;
	int offset;
	if (start.x % 2 == 0)
		offset = Conf::TILE_WIDTH / 2;
	else
		offset = 0;
	temp.x = start.y * Conf::TILE_WIDTH + offset + Conf::TILE_WIDTH * 0.5;
	temp.y = start.x * Conf::TILE_HEIGHT / 2 + Conf::TILE_HEIGHT * 0.5;
	position = temp;
	xyPosition = start;

	while(true){
		if(iter == vstep.size() - 1) break;
		if (!exit) {
			lastPos = Map::coords2XY(position.x, position.y);
			exit = true;
		}
		if (iter != vstep.size() - 1) {
			Path::PathType e = getTypeAtPrec(Map::coords2XY(position.x, position.y));
			switch (e) {
			case Path::EN:
				move(sf::Vector2f(0, -1), 1);
				enemypos.push_back(Vec3Enemy(position,2));
				break;
			case Path::ES:
				move(sf::Vector2f(-1, 0), 1);
				enemypos.push_back(Vec3Enemy(position,4));
				break;
			case Path::EW:
				if (iteratorVec3Enemy == 0) {
					float x = Map::XY2Coords(xyPosition.x, xyPosition.y).x;
					float y = Map::XY2Coords(xyPosition.x, xyPosition.y).y;
					enemypos.push_back(Vec3Enemy(sf::Vector2f(x + Conf::TILE_WIDTH * 0.75f + 0.1f,
							y + Conf::TILE_HEIGHT * 0.75f + 0.1f),3));
				}else{
				move(sf::Vector2f(-1, -0.5), 1);
				enemypos.push_back(Vec3Enemy(position,3));
				}
				break;
			case Path::NE:
				move(sf::Vector2f(0, 1), 1);
				enemypos.push_back(Vec3Enemy(position,6));
				break;
			case Path::NS:
				if (iteratorVec3Enemy == 0) {
					float x = Map::XY2Coords(xyPosition.x, xyPosition.y).x;
					float y = Map::XY2Coords(xyPosition.x, xyPosition.y).y;
					enemypos.push_back(Vec3Enemy(sf::Vector2f(x + Conf::TILE_WIDTH * 0.75f + 0.1f,
							y + Conf::TILE_HEIGHT * 0.25f + 0.1f),5));
				}else{
				move(sf::Vector2f(-1, 0.5), 1);
				enemypos.push_back(Vec3Enemy(position,5));
				}
				break;
			case Path::NW:
				move(sf::Vector2f(-1, 0), 1);
				enemypos.push_back(Vec3Enemy(position,4));
				break;
			case Path::SE:
				move(sf::Vector2f(1, 0), 1);
				enemypos.push_back(Vec3Enemy(position,0));
				break;
			case Path::SN:
				if (iteratorVec3Enemy == 0) {
					float x = Map::XY2Coords(xyPosition.x, xyPosition.y).x;
					float y = Map::XY2Coords(xyPosition.x, xyPosition.y).y;
					enemypos.push_back(Vec3Enemy(sf::Vector2f(x + Conf::TILE_WIDTH / 4.0f + 0.1f,
							y + Conf::TILE_HEIGHT * 0.75f + 0.1f),1));
				}else{
				move(sf::Vector2f(1, -0.5), 1);
				enemypos.push_back(Vec3Enemy(position,1));
				}
				break;
			case Path::SW:
				move(sf::Vector2f(0, -1), 1);
				enemypos.push_back(Vec3Enemy(position,2));
				break;
			case Path::WE:
				if (iteratorVec3Enemy == 0) {
					float x = Map::XY2Coords(xyPosition.x, xyPosition.y).x;
					float y = Map::XY2Coords(xyPosition.x, xyPosition.y).y;
					enemypos.push_back(Vec3Enemy(sf::Vector2f(x + Conf::TILE_WIDTH * 0.25f + 0.1f,
							y + Conf::TILE_HEIGHT * 0.25f + 0.1f),7));
				}else{
				move(sf::Vector2f(1, 0.5), 1);
				enemypos.push_back(Vec3Enemy(position,7));
				}
				break;
			case Path::WN:
				move(sf::Vector2f(1, 0), 1);
				enemypos.push_back(Vec3Enemy(position,0));
				break;
			case Path::WS:
				move(sf::Vector2f(0, 1), 1);
				enemypos.push_back(Vec3Enemy(position,6));
				break;
			}
			++iteratorVec3Enemy;
			if (lastPos != Map::coords2XY(position.x, position.y)) {
				lastPos = xyPosition;
				xyPosition = Map::coords2XY(position.x, position.y);
				exit = false;
				++iter;
				iteratorVec3Enemy = 0;
			}
		}
	}

//	for(size_t i = 0 ; i < enemypos.size() ; ++i){
//		LOGD("LP : %ld, x = %f, y = %f, frame = %d",i ,enemypos.at(i).getPosition().x,enemypos.at(i).getPosition().y,enemypos.at(i).getFrame());
//	}
}
void Path::updateVa() {
	LOGF("Path::updateVa");

	if(vstep.size()==0) return;

	sf::Vector2i pos=start;
	sf::Vector2f p;

	size_t i=0;
	int shift=0;

	PathDir last=vstep[0];

	switch(last) {
		case goN:
		case goS: {shift=0;}break;
		case goW:
		case goE: {shift=128;}break;
	}

	bool visible;
	sf::Vertex v0,v1,v2,v5;

	sf::FloatRect fr;

	sf::Vector2f siz=Conf::vw.getSize();
	sf::Vector2f ctr=Conf::vw.getCenter();

	fr.left=ctr.x-siz.x/2;
	fr.top=ctr.y-siz.y/2;
	fr.width=siz.x;
	fr.height=siz.y;

	if(fr!=lastFr) {
		lastFr=fr;
		va.resize(0);

		int startx;
		int starty;
		int endx;
		int endy;

		sf::Vector2i start=Map::coords2XYABS(fr.left, fr.top);
		sf::Vector2i end=Map::coords2XYABS(fr.left+fr.width, fr.top+fr.height);
		start.x-=2;
		start.y-=1;

		end.x+=2;
		end.y+=2;

		if(start.x >=0) startx=start.x; else startx=0;
		if(start.y >=0) starty=start.y; else starty=0;
		if(end.x < Conf::MAP_WIDTH) endx=end.x; else endx=Conf::MAP_WIDTH;
		if(end.y < Conf::MAP_HEIGHT) endy=end.y; else endy=Conf::MAP_HEIGHT;


		for(size_t iter=0; iter <= vstep.size(); ++iter) {
			visible=false;

			if(
				pos.x >= startx &&
				pos.x < endx &&
				pos.y >= starty &&
				pos.y < endy
				) visible=true;

			if(visible) {
				p=Map::XY2Coords(pos.x, pos.y);

				v0.position=p;
				v1.position=p+sf::Vector2f(Conf::TILE_WIDTH,0.0f);
				v2.position=p+sf::Vector2f(Conf::TILE_WIDTH,Conf::TILE_HEIGHT);
				v5.position=p+sf::Vector2f(0.0f,Conf::TILE_HEIGHT);

				shift/=Conf::textureDivisor;
				int w=256/Conf::textureDivisor;
				int h=128/Conf::textureDivisor;
				v0.texCoords=sf::Vector2f(0,0+shift);
				v1.texCoords=sf::Vector2f(w,0+shift);
				v2.texCoords=sf::Vector2f(w,h+shift);
				v5.texCoords=sf::Vector2f(0,h+shift);

				srand(iter*vstep.size());
				int c=220+rand()%35;
				v0.color=sf::Color(c,c,c);
				c=220+rand()%35;
				v1.color=sf::Color(c,c,c);
				c=220+rand()%35;
				v2.color=sf::Color(c,c,c);
				c=220+rand()%35;
				v5.color=sf::Color(c,c,c);


				va.append(v0);
				va.append(v1);
				va.append(v2);
				va.append(v0);
				va.append(v2);
				va.append(v5);
			}

			if(iter==vstep.size()) {
				lastPathPos = pos;
//				LOGD("%d %d", pos.x, pos.y);
				break;
			}

			PathDir e=vstep[iter];
			switch(e) {
				case goN: {
					switch(last) {
						case goN:
						case goS: {shift=0; if(pos.x-- % 2==0) {++pos.y;}++iterator;}break;
						case goW: {shift=640; if(pos.x-- % 2!=0) {--pos.y;}++iterator;}break;
						case goE: {shift=512; if(pos.x++ % 2==0) {++pos.y;}++iterator;}break;
					}
				}break;
				case goS: {
					switch(last) {
						case goN:
						case goS: {shift=0; if(pos.x++ % 2!=0) {--pos.y;}++iterator;}break;
						case goW: {shift=256; if(pos.x-- % 2!=0) {--pos.y;}++iterator;}break;
						case goE: {shift=384; if(pos.x++ % 2==0) {++pos.y;}++iterator;}break;
					}
				}break;
				case goW: {
					switch(last) {
						case goN: {shift=384; if(pos.x-- % 2==0) {++pos.y;}++iterator;}break;
						case goS: {shift=512; if(pos.x++ % 2!=0) {--pos.y;}++iterator;}break;
						case goW:
						case goE: {shift=128; if(pos.x-- % 2!=0) {--pos.y;}++iterator;}break;
					}
				}break;
				case goE: {
					switch(last) {
						case goN: {shift=256; if(pos.x-- % 2==0) {++pos.y;}++iterator;}break;
						case goS: {shift=640; if(pos.x++ % 2!=0) {--pos.y;}++iterator;}break;
						case goW:
						case goE: {shift=128; if(pos.x++ % 2==0) {++pos.y;}++iterator;}break;
					}
				}break;
			}
			if(iterator == 1) tileAfterStart = sf::Vector2i(pos.x,pos.y);
			last=e;
			i+=6;
		}

	}

}
void Path::string2path(std::string s) {
	vstep.clear();
	for(size_t i=0; i<s.size(); ++i) {
		switch(s[i]) {
			case 'n':
			case 'N':
			vstep.push_back(goN);
			break;
			case 's':
			case 'S':
			vstep.push_back(goS);
			break;
			case 'w':
			case 'W':
			vstep.push_back(goW);
			break;
			case 'e':
			case 'E':
			vstep.push_back(goE);
			break;
		}
	}
	if(vstep.size()==0) {
		vstep.push_back(goN);
	}

	veci.resize(vstep.size());
	sf::Vector2i pos=start;
	PathDir now,last=vstep[0];
	for(size_t i=0; i<veci.size(); ++i) {
		veci[i]=pos;
		now=vstep[i];
		nextVec2i(pos,now,last);
		last=now;
	}

	pos=start;
	last=vstep[0];

	PathType pt;
	PathType ptprec;

	switch(vstep[0]) {
		case goN:
		pt=NS;
		ptprec = SN;
		break;
		case goS:
		pt=NS;
		ptprec = NS;
		break;
		case goE:
		pt=WE;
		ptprec = WE;
		break;
		case goW:
		pt=WE;
		ptprec = EW;
		break;
	}

	vtype.clear();
	vtypeprec.clear();
	vtypeprec.push_back(ptprec);
	for(size_t iter=0; iter <= vstep.size(); ++iter) {
		if(iter==vstep.size()) break;

		PathDir now=vstep[iter];
		nextVec2i(pos,now,last);

		switch(last) {
			case goN: {
				switch(now) {
					case goS:
					case goN: pt=NS;ptprec=SN; break;
					case goW: pt=SW;ptprec=SW; break;
					case goE: pt=SE;ptprec=SE; break;
				}
			}break;
			case goS: {
				switch(now) {
					case goN:
					case goS: pt=NS;ptprec=NS;break;
					case goW: pt=NW;ptprec=NW; break;
					case goE: pt=NE;ptprec=NE; break;
				}
			}break;
			case goW: {
				switch(now) {
					case goN: pt=NE;ptprec=EN; break;
					case goS: pt=SE;ptprec=ES; break;
					case goE:
					case goW: pt=WE;ptprec=EW; break;
				}
			}break;
			case goE: {
				switch(now) {
					case goN: pt=NW;ptprec=WN; break;
					case goS: pt=SW;ptprec=WS; break;
					case goW:
					case goE: pt=WE;ptprec=WE; break;
				}
			}break;
		}
		last=now;

		vtype.push_back(pt);
		vtypeprec.push_back(ptprec);
	}
}
bool Path::isCollide(sf::Vector2i p)const {
	sf::Vector2i pos=start;
	PathDir last=vstep[0];

	for(size_t iter=0; iter <= vstep.size(); ++iter) {
		if(p==pos) return true;
		if(iter==vstep.size()) break;

		PathDir now=vstep[iter];
		nextVec2i(pos,now,last);
		last=now;
	}
	return false;
}
void Path::nextVec2i(sf::Vector2i &p, PathDir now, PathDir last) const {
	switch(now) {
		case goN: {
			switch(last) {
				case goN:
				case goS: {if(p.x-- % 2==0) {++p.y;}}break;
				case goW: {if(p.x-- % 2!=0) {--p.y;}}break;
				case goE: {if(p.x++ % 2==0) {++p.y;}}break;
			}
		}break;
		case goS: {
			switch(last) {
				case goN:
				case goS: {if(p.x++ % 2!=0) {--p.y;}}break;
				case goW: {if(p.x-- % 2!=0) {--p.y;}}break;
				case goE: {if(p.x++ % 2==0) {++p.y;}}break;
			}
		}break;
		case goW: {
			switch(last) {
				case goN: {if(p.x-- % 2==0) {++p.y;}}break;
				case goS: {if(p.x++ % 2!=0) {--p.y;}}break;
				case goW:
				case goE: {if(p.x-- % 2!=0) {--p.y;}}break;
			}
		}break;
		case goE: {
			switch(last) {
				case goN: {if(p.x-- % 2==0) {++p.y;}}break;
				case goS: {if(p.x++ % 2!=0) {--p.y;}}break;
				case goW:
				case goE: {if(p.x++ % 2==0) {++p.y;}}break;
			}
		}break;
	}
}
const std::vector<sf::Vector2i> &Path::getAsVector()const {
	return veci;
}
Path::PathType Path::getTypeAtPrec(sf::Vector2i p)const {
	PathType pt=NS;

	for(size_t i=0; i<veci.size(); ++i) {
		if(veci[i]==p) {
			if(i < vtypeprec.size()) {
				pt=vtypeprec[i];
			} else {
				LOGE("Path::getTypeAtPrec error: veci.size != vtypeprec.size");
			}
			break;
		}
	}
	return pt;
}
Path::PathType Path::getTypeAt(sf::Vector2i p)const {
	PathType pt=NS;

	for(size_t i=0; i<veci.size(); ++i) {
		if(veci[i]==p) {
			if(i < vtype.size()) {
				pt=vtype[i];
			} else {
				LOGE("Path::getTypeAt error: veci.size != vtype.size");
			}
			break;
		}
	}
	return pt;
}

void Path::updateVaForce() {
	lastFr.height=-1;
	lastFr.width=-1;
	lastFr.left=0;
	lastFr.top=0;
	updateVa();

}
