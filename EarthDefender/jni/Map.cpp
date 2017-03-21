/*
 * Map.cpp
 *
 *  Created on: 20 kwi 2016
 *      Author: Piotr Okoń
 */

#include "Map.hpp"
#include "Textures.hpp"
#include "Conf.hpp"
#include <SFML/Window/Touch.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <string>

#include "Gatling.hpp"
#include "LightCannon.hpp"
#include "Coil.hpp"
#include "LightHoverCraft.hpp"
#include "LightBomber.hpp"
#include "log.hpp"
#include "RocketLauncher.hpp"

Map::Map():
	Observable("Map", "map", "game"),
	selected(sf::Vector2i(-1, -1)),
	visibleBoundsInit(false),
	killedEnemiesCounter(0),
	lastNonActivatedEnemy(0),
	spawnedEnemies(0),
	fpsLimit(PAUSEFPSLIMIT)
{
	lastEnemyTime = Conf::clock.getElapsedTime().asSeconds();

	sf::FloatRect fr;
	fr.width = Conf::MAP_WIDTH * Conf::TILE_WIDTH * 0.5f;
	fr.height = Conf::MAP_HEIGHT * Conf::TILE_HEIGHT;
//		groundShadow.generate(16, fr, GroundShadow::medium, 1000, 2000, 16, 48, 10);

	path.setTexture("map.asphalt");
	path.setStart(sf::Vector2i(0, 0));
	path.string2path(
			"eeeeeennwnneeeessssswwsswwwseeeeeeeennneeennnwwwnnneeeeee"
//				"eeeeeeeeeeeeeeeeeennwnneeeess"
			);

	path.updateVa();
	path.initVec3Enemy();

	animatedGround.setTexture("map.grassanim");
	animatedGround.updatePath(path);

	LOGE("last path pos: %dx%d", path.getLastPathPos().x, path.getLastPathPos().y);
	base.setBasePosition(path.getLastPathPos());

//		drawVec.resize(Conf::MAP_HEIGHT*Conf::MAP_WIDTH);
}
void Map::notify(ListenerMessage &msg) {
	if(Conf::debugEnable) {
		std::string a;
		a = "Map::notify: Class: " + msg.classname + " Object: " + msg.objectname
				+ " Parent: " + msg.parentname + " | ";
		for (auto &e : msg.changes) {
			a += e.first + "=" + e.second + "; ";
		}
		//LOGD("%s", a.c_str());
	}

	if (msg.classname == S::class_tower){
		if (!msg.changes[S::cmd_money_plus].empty()
				|| !msg.changes[S::cmd_money_minus].empty()) {
			lmsg.changes.clear();
			lmsg.changes[S::cmd_money_plus] = msg.changes[S::cmd_money_plus];
			lmsg.changes[S::cmd_money_minus] = msg.changes[S::cmd_money_minus];
			notifyListeners();
		}
	} else if(msg.classname == S::class_enemy){
		if(!msg.changes[S::cmd_revalidate].empty()){
			int ox, nx;
			int oy, ny;
			std::sscanf(msg.changes[S::cmd_revalidate].c_str(), "%d %d %d %d",&ox, &oy, &nx, &ny);

			void *checkptr=msg.sender;

			sf::Vector2i id(ox,oy);
			auto i=drawVec[id].begin();
			auto iend=drawVec[id].end();

			for(; i != iend; ++i){
				if(checkptr == *i){
					drawVec[id].erase(i);
					break;
				}
			}
//			LOGE("nx:%d ny:%d sender:%d", nx, ny, msg.sender);
			drawVec[sf::Vector2i(nx,ny)].push_back((Enemy*)msg.sender);
		}

	} else if (msg.classname == S::class_simplebutton) {
		if (msg.parentname == S::panel_build && selected.x != -1 && selected.y != -1 && !isTowerOnTile(selected)) {
			lmsg.changes.clear();
			bool click=false;

			if (ISCLICKED(S::tower_gatling)) {
				towers.push_back(new Gatling(selected));
				drawVec[selected].push_back(*towers.rbegin());

				lmsg.changes[S::cmd_money_minus] = Tower::priceOfS(S::tower_gatling,1);
				click=true;
			} else if (ISCLICKED(S::tower_lightcannon)) {
				towers.push_back(new LightCannon(selected));
				drawVec[selected].push_back(*towers.rbegin());
				lmsg.changes[S::cmd_money_minus] = Tower::priceOfS(S::tower_lightcannon,1);
				click=true;
			} else if (ISCLICKED(S::tower_coil)) {
				towers.push_back(new Coil(selected));
				drawVec[selected].push_back(*towers.rbegin());
				lmsg.changes[S::cmd_money_minus] = Tower::priceOfS(S::tower_coil,1);
				click=true;
			} else if(ISCLICKED(S::tower_rocketlauncher)){
				towers.push_back(new RocketLauncher(selected));
				drawVec[selected].push_back(*towers.rbegin());
				lmsg.changes[S::cmd_money_minus] = Tower::priceOfS(S::tower_rocketlauncher,1);
				click=true;
			}else if (ISCLICKED(S::btn_close)) {
				click=true;
			}
			if(click){
				lmsg.changes[S::cmd_closepanel] = S::panel_build;
				notifyListeners();
			}
		} else if (msg.parentname == S::panel_tower) {
			if (ISCLICKED(S::btn_close)) {
				sendMessage(S::cmd_closepanel, S::panel_tower);
			} else if (ISCLICKED(S::btn_sell)) {
				for (size_t i = 0; i < towers.size(); ++i) {
					if (towers[i]->getXYPosition() == selected) {
						int cashback = Tower::priceOf(towers[i]->getText(), towers[i]->getLevel());
						cashback *= 0.60;
						std::string str = std::to_string(cashback);

						lmsg.changes.clear();
						lmsg.changes[S::cmd_money_plus] = str;
						lmsg.changes[S::cmd_closepanel] = S::panel_tower;

						notifyListeners();
						drawVec[selected].clear();
						delete towers[i];
						towers.erase(towers.begin() + i);
						break;
					}
				}
			} else if (ISCLICKED(S::btn_upgrade)) {
				for (size_t i = 0; i < towers.size(); ++i) {
					if (towers[i]->getXYPosition() == selected) {
						towers[i]->lvlUp();
						lmsg.changes.clear();
						lmsg.changes[S::cmd_openpanel] = S::panel_tower;
						lmsg.changes[S::cmd_money_minus] = Tower::priceOfS(towers[i]->getText(), towers[i]->getLevel());
						notifyListeners();

						break;
					}
				}
			}
		}else if(msg.parentname == S::panel_targeting){
			if (ISCLICKED(S::btn_close)) {
				lmsg.changes.clear();
				lmsg.changes[S::cmd_closepanel] = S::panel_targeting;
				lmsg.changes[S::cmd_setmenuview] = S::menu_gamegui;
				notifyListeners();
			}else if(ISCLICKED(S::btn_target_first)){
				Tower *t=getSelectedTower();
				if(t!=NULL){
					t->setTargetMethod(FIRST);
					sendMessage(S::cmd_openpanel, S::panel_targeting);
				}
			}else if(ISCLICKED(S::btn_target_last)){
				Tower *t=getSelectedTower();
				if(t!=NULL){
					t->setTargetMethod(LAST);
					sendMessage(S::cmd_openpanel, S::panel_targeting);
				}
			}else if(ISCLICKED(S::btn_target_nearest)){
				Tower *t=getSelectedTower();
				if(t!=NULL){
					t->setTargetMethod(NEAREST);
					sendMessage(S::cmd_openpanel, S::panel_targeting);
				}
			}
		}
	}
}
void Map::drawDrawVec(sf::RenderTarget &target)const{
	sf::Vector2f siz=Conf::vw.getSize();
	sf::Vector2f ctr=Conf::vw.getCenter();

	sf::FloatRect fr;
	fr.left=ctr.x-siz.x/2;
	fr.top=ctr.y-siz.y/2;
	fr.width=siz.x;
	fr.height=siz.y;

	int startx;
	int starty;
	int endx;
	int endy;

	sf::Vector2i start=Map::coords2XYABS(fr.left, fr.top);
	sf::Vector2i end=Map::coords2XYABS(fr.left+fr.width, fr.top+fr.height);
	start.x-=2;
	start.y-=1;
	end.x+=4;
	end.y+=2;
	if(start.x >=0) startx=start.x; else startx=0;
	if(start.y >=0) starty=start.y; else starty=0;
	if(end.x < Conf::MAP_WIDTH) endx=end.x; else endx=Conf::MAP_WIDTH;
	if(end.y < Conf::MAP_HEIGHT) endy=end.y; else endy=Conf::MAP_HEIGHT;

//	LOGE("sx:%d sy:%d ex:%d ey:%d",startx,starty,endx,endy);

	sf::Vector2i p;
	for(p.x=startx; p.x<endx; ++p.x){
		for(p.y=starty; p.y<endy; ++p.y){
//			const std::vector<sf::Drawable*> *v=&drawVec[x+y*Conf::MAP_WIDTH];

			if(drawVec.find(p)==drawVec.end()) continue;
			const std::vector<sf::Drawable*> *v=&drawVec.at(p);

			for(auto i=v->rbegin(); i!=v->rend(); ++i){
//			for(auto i=v->begin(); i!=v->end(); ++i){
				target.draw(**i);
			}
		}
	}
}
void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(animatedGround, states);
	drawSelectedTile(target);
	target.draw(path, states);
	drawDrawVec(target);

	if (isInVisibleBounds(base.getPosition()))
		target.draw(base, states);
	drawTowerRadius(target);
}
sf::Vector2f Map::XY2Coords(int x, int y) {
	sf::Vector2f temp;

	int offset;
	if (x % 2 == 0)
		offset = Conf::TILE_WIDTH / 2;
	else
		offset = 0;
	temp.x = y * Conf::TILE_WIDTH + offset;
	temp.y = x * Conf::TILE_HEIGHT / 2;

	return temp;
}
sf::Vector2i Map::coords2XY(float x, float y) {
	sf::Vector2f temp;
	for (int i = 0; i < Conf::MAP_WIDTH; ++i) {
		for (int j = 0; j < Conf::MAP_HEIGHT; ++j) {
			temp = XY2Coords(i, j);
			int cellCenterX = temp.x + Conf::TILE_WIDTH / 2;
			int cellCenterY = temp.y + Conf::TILE_HEIGHT / 2;

			double dx = std::fabs(x - cellCenterX);
			double dy = std::fabs(y - cellCenterY);
			if (dx / (Conf::TILE_WIDTH * 0.5) + dy / (Conf::TILE_HEIGHT * 0.5) <= 1)
				return sf::Vector2i(i, j);
		}
	}
	return sf::Vector2i(-1, -1);
}
sf::Vector2i Map::coords2XYABS(float x, float y) {
	sf::Vector2i p;

	y*=2;
	p.x=std::round(y/Conf::TILE_HEIGHT);
	p.y=std::round(x/Conf::TILE_WIDTH);

	return p;
}
void Map::update(sf::RenderWindow &rw) {
	LOGF("Map::update");

	if (Conf::gameRun){
		if(fpsLimit != RUNFPSLIMIT){
			fpsLimit = RUNFPSLIMIT;
			rw.setFramerateLimit(fpsLimit);
		}
		animatedGround.updateVa();
		path.updateVa();

		if(!Conf::gamePause){
			animatedGround.update();
			updateEnemies(rw);
			base.update(enemies);
			updateTowers(rw);
			if (!visibleBoundsInit) {
				updateVisibleBounds(rw);
				visibleBoundsInit = true;
			}
			if (Gestures::get() == Gestures::FastTap) {
				sf::Vector2f hp = Gestures::getHoldPoint(0);
				selected = coords2XY(hp.x, hp.y);
				if (selected.x != -1 && selected.y != -1) {
					int t;
					(isTowerOnTile(selected)) ? t = 1 : t = 0;
					if (!path.isCollide(selected)) {
						if (!isTowerOnTile(selected)) {
							sendMessage(S::cmd_closepanel, S::panel_all);
							lmsg.changes.clear();
							lmsg.changes[S::cmd_openpanel]=S::panel_build;
							lmsg.changes[S::cmd_setmenuview]=S::menu_gamegui;
							notifyListeners();
						} else {
							sendMessage(S::cmd_closepanel, S::panel_all);
							sendMessage(S::cmd_openpanel, S::panel_tower);
							lmsg.changes.clear();
							lmsg.changes[S::cmd_openpanel]=S::panel_targeting;
							lmsg.changes[S::cmd_setmenuview]=S::menu_empty;
							notifyListeners();
						}
					} else {
						selected.y = selected.x = -1;

						lmsg.changes.clear();
						lmsg.changes[S::cmd_closepanel]=S::panel_all;
						lmsg.changes[S::cmd_setmenuview]=S::menu_gamegui;
						notifyListeners();
					}
				} else {
					lmsg.changes.clear();
					lmsg.changes[S::cmd_closepanel]=S::panel_all;
					lmsg.changes[S::cmd_setmenuview]=S::menu_gamegui;
					notifyListeners();
				}
			} else if (Gestures::get() == Gestures::Slide) {
				sf::Vector2f nctr = Conf::vw.getCenter()
						+ Gestures::getSlideSpeed();
				Conf::vw.setCenter(nctr);
				sendMessage(S::cmd_review, S::one);
			} else if (Gestures::get() == Gestures::Pinch) {
				zoom(Gestures::getPinchVal());
			}
		}else{
			if(fpsLimit != PAUSEFPSLIMIT){
				fpsLimit=PAUSEFPSLIMIT;
				rw.setFramerateLimit(fpsLimit);
			}
		}
	}else{
		for(auto &d: drawVec){
			d.second.clear();
		}
		for (auto &e : enemies) {
			delete e;
		}
		enemies.clear();

		for (auto &t : towers) {
			delete t;
		}
		towers.clear();
	}
}
void Map::zoom(int delta) {
	if (delta > 0) {
		Conf::newzoom *= std::pow(1.003f, delta);
		if (Conf::newzoom > 1.5f / Conf::gs)
			Conf::newzoom = 1.5f / Conf::gs;

		sendMessage(S::cmd_review, S::one);
		Gestures::clear();
	} else if (delta < 0) {
		Conf::newzoom *= std::pow(0.997f, -delta);
		if (Conf::newzoom < 0.25f / Conf::gs)
			Conf::newzoom = 0.25f / Conf::gs;

		sendMessage(S::cmd_review, S::one);
		Gestures::clear();
	}
}
void Map::updateTowers(sf::RenderWindow &rw) {
	LOGF("Map::updateTowers");
	for (size_t i = 0; i < towers.size(); ++i) {
		towers[i]->update(enemies);
	}
}
void Map::updateEnemies(sf::RenderWindow &rw) {
	LOGF("Map::updateEnemies, lastNonActivatedEnemy: %d", lastNonActivatedEnemy);

	if (
			enemies.size() > 0 &&
			lastNonActivatedEnemy > 0 &&
			Conf::clock.getElapsedTime().asSeconds() - lastEnemyTime >= spawnTime[lastNonActivatedEnemy]
		) {
		LOGF("Map::updateEnemies spawnEnemy ");
		if (spawnTime[lastNonActivatedEnemy] >= 10.f || spawnTime[lastNonActivatedEnemy] == 0.f) {
			sendMessage(S::cmd_pluswave, S::one);
		}
		enemies[lastNonActivatedEnemy--]->setEnabled(true);
		lastEnemyTime = Conf::clock.getElapsedTime().asSeconds();
		if (lastNonActivatedEnemy > 0) {
			if (spawnTime[lastNonActivatedEnemy] >= 10.f) {
				sendMessage(S::cmd_next_wave, S::one);
			}
			else
				sendMessage(S::cmd_next_wave, S::zero);
		}
	}

	std::vector<Enemy*>::iterator onedel;
	bool deleting=false;

	for (auto i = enemies.begin(); i != enemies.end(); ++i) {
		if (!deleting && (*i)->getHP() <= 0) {
			LOGF("Map::updateEnemies hp <= 0");
			if ((*i)->getErase()) {
				LOGF("Map::updateEnemies getErase == true");

				if((*i)->getHP() > -10000){
					LOGF("Map::updateEnemies hp > -10000");

					std::string val;
					val = Enemy::priceOfS((*i)->getText());
					sendMessage(S::cmd_money_plus, val);
					++killedEnemiesCounter;
				}
				onedel=i;
				deleting=true;
			}
			(*i)->destroyIt();
		}
		(*i)->update(path.Vec3EnemyPos(),base.getPosition());
	}

	if(deleting){
		sf::Vector2i p=(*onedel)->getAnim().getXYPosition();
		auto vb=drawVec[p].begin();
		auto vend=drawVec[p].end();

		for(;vb!=vend; ++vb){
			if(*vb == *onedel){
				drawVec[p].erase(vb);
				break;
			}
		}
		delete *onedel;
		enemies.erase(onedel);
	}
}
void Map::updateVisibleBounds(sf::RenderWindow &rw) {
	LOGF("Map::updateVisibleBounds");

	sf::Vector2f leftTopPos = rw.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f rightBotPos = rw.mapPixelToCoords(
			sf::Vector2i(Conf::dWidth, Conf::dHeight));

	visibleBounds.left = leftTopPos.x - 2 * Conf::TILE_WIDTH;
	visibleBounds.top = leftTopPos.y - 2 * Conf::TILE_HEIGHT;
	visibleBounds.width = rightBotPos.x - leftTopPos.x + 4 * Conf::TILE_WIDTH;
	visibleBounds.height = rightBotPos.y - leftTopPos.y + 4 * Conf::TILE_HEIGHT;
}
inline bool Map::isInVisibleBounds(sf::Vector2f pos) const {
	return pos.x > visibleBounds.left
			&& pos.x < visibleBounds.left + visibleBounds.width
			&& pos.y > visibleBounds.top
			&& pos.y < visibleBounds.top + visibleBounds.height;
}
void Map::drawTowerRadius(sf::RenderTarget &target) const {
	for (size_t i = 0; i < towers.size(); ++i) {
		if (selected == towers[i]->getXYPosition()) {
			float x = Conf::clock.getElapsedTime().asSeconds() * 4;
			float sinx = std::sin(x);

			sf::CircleShape circle;
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineThickness(4 + 4 * std::fabs(sinx));
			circle.setOutlineColor(sf::Color(0, 255, 255, 128 + 127 * std::fabs(sinx)));
			circle.setRadius(Conf::TILE_WIDTH / 2 + towers[i]->getRange() * Conf::TILE_WIDTH + 4 * sinx);
			circle.setPosition(sf::Vector2f(towers[i]->getPosition().x,towers[i]->getPosition().y));
			circle.setScale(1.0f, 0.5f);
			circle.setPointCount(64);

			circle.setRadius(circle.getRadius() - 160);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			target.draw(circle);

			circle.setRadius(circle.getRadius() + 80);
			circle.setOutlineColor(
					circle.getOutlineColor() * sf::Color(255, 255, 255, 64));
			circle.setOutlineThickness(circle.getOutlineThickness() + 10);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			target.draw(circle);

			circle.setOutlineColor(
					circle.getOutlineColor() * sf::Color(255, 255, 255, 64));
			circle.setRadius(circle.getRadius() + 80);
			circle.setOutlineThickness(circle.getOutlineThickness() + 10);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			target.draw(circle);


			if (Conf::debugEnable) {
				if (towers[i]->getTargetedEnemy() != NULL) {
					sf::Vector2f temp = towers[i]->getTargetedEnemy()->getAnim().getPosition();
					if (towers[i]->getTargetedEnemy()->isFlying()) temp.y -= 78;
					sf::Vertex line[] ={
						sf::Vertex(towers[i]->getPosition()),
						sf::Vertex(temp)
					};

					target.draw(line, 2, sf::Lines);
				}
			}

			break;
		}
	}
}
bool Map::isTowerOnTile(sf::Vector2i i) const {
	LOGF("Map::isTowerOnTile");
	for (size_t j = 0; j < towers.size(); ++j) {
		if (towers[j]->getXYPosition() == i)
			return true;
	}
	return false;
}
void Map::drawSelectedTile(sf::RenderTarget &target) const {
	if (selected.x != -1 && selected.y != -1) {
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(Conf::TILE_WIDTH, Conf::TILE_HEIGHT));
		r.setTexture(&Textures::get(S::tex_map_selectedtile));
		r.setPosition(XY2Coords(selected.x, selected.y));
		r.setFillColor(sf::Color(255, 255, 255, 128 + 127 * std::fabs(std::sin(6 * CLOCKASSEC))));
		target.draw(r);
	}
}
Tower* Map::getSelectedTower() {
	for (auto &t : towers) {
		if (selected == t->getXYPosition()) {
			return t;
		}
	}
	return NULL;
}
void Map::spawningInit(size_t i) {
	killedEnemiesCounter = 0;
	spawnedEnemies = i;
	lastNonActivatedEnemy = i - 1;
	spawnTime.clear();
	
	for (size_t j = 0; j < i; ++j)
		spawnTime.push_back(0.f);
	
	size_t j = i - 1;
	for (; j >= i - 5; --j) { //1st wave
		spawnTime[j] = 0.7f;		
	}
	spawnTime[j--] = 30.f;
	i = j + 2;

	for (; j >= i - 5; --j) { //2nd wave
		spawnTime[j] = 0.5f;
	}
	spawnTime[j--] = 30.f;
	i = j + 2;

	for (; j >= i - 5; --j) { //3rd wave
		spawnTime[j] = 0.4f;
	}
	spawnTime[j--] = 30.f;
	i = j + 2;

	for (; j >= i - 5; --j) { //4th wave
		spawnTime[j] = 0.4f;
	}
	spawnTime[j--] = 30.f;
	i = j + 2;

	for (; j >= i - 5; --j) { //5th wave
		spawnTime[j] = 0.6f;
	}
	spawnTime[j--] = 30.f;
	i = j + 2;

	for (; j > i - 10; --j) { //6th wave
		spawnTime[j] = 0.3f;
	}
	spawnTime[j--] = 50.f;
	i = j + 2;

	for (; j > 0; --j) { //7th wave
		spawnTime[j] = 0.3f;
	}
}
void Map::refreshAllTextures(){
	for(auto &e : enemies){
		e->refreshTexture();
	}
	for(auto &e : towers){
		e->refreshAnim();
	}

	animatedGround.refreshTexture();
	path.refreshTexture();
	path.updateVaForce();
	base.refreshAnim();
}
