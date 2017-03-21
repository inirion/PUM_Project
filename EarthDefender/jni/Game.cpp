#include "Game.hpp"
#include "LightBomber.hpp"
#include "LightHoverCraft.hpp"

Game::Game(sf::View &view, sf::RenderWindow &win):
	rw(win),
	debugText("",Conf::fMono,32),
	initThread(&Game::initGame, this),
	dirty(false),
	loading(false),
	baseDestroy(false),
	backgroundEnable(true),
	money(0),
	enemyCount(0),
	loadedEnemies(0),
	enemiesKilled(0),
	baseMaxHP(1000),
	baseHP(baseMaxHP),
	time(0.0f),
	startBaseDestroyTime(0.0f),
	debugTextTime(0.0f),
	currentWave(1),
	maxWaves(7)
{
	//InitThread = sf::Thread(&Game::InitThread, this);
	sBackground.setTexture(&Textures::get(S::tex_background));

	backgroundResize();

	mainMenu.listenAllViews(this);
	panelManager.listenAllPanels(&map);
	map.addListener(this);
	map.getBase().addListener(this);

#define SETPRICE(T) 		panelManager.getMap()[S::panel_build].getButtonMap()[T].setText(Tower::priceOfS(T,1));
	SETPRICE(S::tower_gatling);
	SETPRICE(S::tower_lightcannon);
	SETPRICE(S::tower_coil);
	SETPRICE(S::tower_rocketlauncher);
}
void Game::events() {
	LOGF("Game::events");
	Gestures::update(rw);
	mainMenu.update(rw);
	panelManager.update(rw);
	map.update(rw);
}
void Game::drawDebugInfo() {
	LOGF("Game::drawDebugInfo");


	if (Conf::debugEnable) {
		if (Conf::clock.getElapsedTime().asSeconds() > debugTextTime + 1.0f) {
			debugTextTime = Conf::clock.getElapsedTime().asSeconds();

			sf::Vector2f ctr = rw.getView().getCenter();
			std::string str;
			str = "Dtime: " + std::to_string(Conf::dtime) + "\nFPS: "
					+ std::to_string(1 / Conf::dtime) + "\nWxH: "
					+ std::to_string(Conf::dWidth) + " x "
					+ std::to_string(Conf::dHeight) + "\nzoom: "
					+ std::to_string(Conf::zm) + "\nguiScale: "
					+ std::to_string(Conf::gs) + "\nhoverPos: "
					+ std::to_string((int) Conf::hoverPos.x) + " x "
					+ std::to_string((int) Conf::hoverPos.y) + "\nruntime: "
					+ std::to_string(
							(int) Conf::clock.getElapsedTime().asSeconds())
					+ "\nctr: " + std::to_string((long) ctr.x) + " x "
					+ std::to_string((long) ctr.y) + "\ngameRun: "
					+ std::to_string(Conf::gameRun) + "\ngamePause: "
					+ std::to_string(Conf::gamePause) + "\nview: "
					+ mainMenu.getSelected()->getText();

			debugText.setCharacterSize(0.033 * Conf::dHeight);

			debugText.setString(str);
		}

		debugText.setScale(Conf::zm, Conf::zm);
		debugText.setFillColor(sf::Color(0, 0, 0, 128));
		debugText.setPosition(
				rw.mapPixelToCoords(
						sf::Vector2i(80 * Conf::gs, 80 * Conf::gs)));
		rw.draw(debugText);
		debugText.move(sf::Vector2f(2 * Conf::zm, 2 * Conf::zm));
		rw.draw(debugText);
		debugText.setFillColor(sf::Color(255, 255, 255, 128));
		debugText.move(sf::Vector2f(-1 * Conf::zm, -1 * Conf::zm));
		rw.draw(debugText);
	}
}
void Game::backgroundDraw() {
	LOGF("Game::backgroundDraw");


	if (backgroundEnable) {
		sBackground.setPosition( rw.mapPixelToCoords( sf::Vector2i( (Conf::dWidth - sBackground.getLocalBounds().width) * 0.5f, 0)));
		sBackground.setScale(Conf::zm, Conf::zm);
		rw.draw(sBackground);

	}
	if (loading) {
		drawLoadingScreen();
	}
}
void Game::drawMenu() {
	LOGF("Game::drawMenu");

	if (Conf::gameRun && Conf::gamePause) {
		sf::RectangleShape rs(
				sf::Vector2f(Conf::dWidth * Conf::zm,
						Conf::dHeight * Conf::zm));
		rs.setPosition(rw.mapPixelToCoords(sf::Vector2i(0, 0)));
		rs.setFillColor(sf::Color(0, 0, 0, 128));
		rw.draw(rs);
	}

	rw.draw(mainMenu);
}
void Game::gameDraw() {
	LOGF("Game::gameDraw");

	if (Conf::gameRun) {
		rw.draw(map);
		drawStatusBar();
		rw.draw(panelManager);
		if (baseDestroy) {
			destroyBase();
		}
	}
}
void Game::review() {
	LOGF("Game::review");

	Conf::zm = Conf::newzoom;
	Conf::vw.setSize(Conf::dWidth * Conf::zm, Conf::dHeight * Conf::zm);
	rw.setView(Conf::vw);
	cameraCheck();
}
void Game::cameraCheck() {
	LOGF("Game::cameraCheck");

	sf::Vector2f ctr = Conf::vw.getCenter();
	sf::Vector2f p1 = Map::XY2Coords(0, 0);
	sf::Vector2f p2 = Map::XY2Coords(Conf::MAP_WIDTH, Conf::MAP_HEIGHT);

	if (ctr.x < p1.x)
		ctr.x = p1.x;
	if (ctr.y < p1.y)
		ctr.y = p1.y;
	if (ctr.x > p2.x)
		ctr.x = p2.x;
	if (ctr.y > p2.y)
		ctr.y = p2.y;

	Conf::vw.setCenter(ctr);
	rw.setView(Conf::vw);
	map.updateVisibleBounds(rw);
}
void Game::moneyHandle() {
	LOGF("Game::moneyHandle");

#define CHECKPRICE(T) \
		if(money >= Tower::priceOf(T, 1)){\
			panelManager.getMap()[S::panel_build].getButtonMap()[T].setTextColor(sf::Color::Green); \
			panelManager.getMap()[S::panel_build].getButtonMap()[T].setEnabled(true);\
		}\
		else{\
			panelManager.getMap()[S::panel_build].getButtonMap()[T].setTextColor(sf::Color::Black);\
			panelManager.getMap()[S::panel_build].getButtonMap()[T].setEnabled(false); \
		}
	CHECKPRICE(S::tower_coil);
	CHECKPRICE(S::tower_gatling);
	CHECKPRICE(S::tower_lightcannon);
	CHECKPRICE(S::tower_rocketlauncher);
}
void Game::towerPanelHandle() {
	LOGF("Game::towerPanelHandle");

	Tower *t = map.getSelectedTower();

	if (t != NULL) {
		panelManager.getMap()[S::panel_tower].setText(t->getText());

		char rng[16];
		sprintf(rng, "%.1f", t->getRange());
		//std::string req = t->getText() + "."+ std::to_string(t->getLevel() + 1);
		int upprice = Tower::priceOf(t->getText(), t->getLevel() + 1);

		std::string info =
		ll("level")+": "+std::to_string(t->getLevel())+"[br]"+
		ll("range")+": "+rng+"[br]"+
		ll("damage")+": "+std::to_string(t->getMinDmg())+" - " + std::to_string(t->getMaxDmg()) +"[br]";
		if (!t->isMaxLevel())
			info += ll("upgrade-cost")+": "+std::to_string(upprice);

		panelManager.getMap()[S::panel_tower].getButtonMap()["info"].setText(info);

		if (t->isMaxLevel()) {
			panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setVisible(false);
		} else {
			panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setVisible(true);

			if (money > upprice) {
				panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setEnabled(true);
				panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setTextColor(sf::Color::Green);
			} else {
				panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setEnabled(false);
				panelManager.getMap()[S::panel_tower].getButtonMap()[S::btn_upgrade].setTextColor(sf::Color::Black);
			}
		}
	}
}
void Game::targetPanelHandle() {
	Tower *t = map.getSelectedTower();

	if (t != NULL) {
		switch(t->getTargetMethod()){
		case FIRST:
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_first].setTexture(S::tex_checked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_last].setTexture(S::tex_unchecked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_nearest].setTexture(S::tex_unchecked);
			break;
		case LAST:
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_first].setTexture(S::tex_unchecked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_last].setTexture(S::tex_checked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_nearest].setTexture(S::tex_unchecked);
			break;
		case NEAREST:
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_first].setTexture(S::tex_unchecked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_last].setTexture(S::tex_unchecked);
			panelManager.getMap()[S::panel_targeting].getButtonMap()[S::btn_target_nearest].setTexture(S::tex_checked);
			break;
		}
	}
}
void Game::notify(ListenerMessage &msg) {
	if (Conf::debugEnable) {
		std::string a;
		a = "Game::notify: Class: " + msg.classname + " Object: "
				+ msg.objectname + " Parent: " + msg.parentname + " | ";
		for (auto &e : msg.changes) {
			a += e.first + "=" + e.second + "; ";
		}
		LOGD("%s", a.c_str());
	}

	if(msg.changes[S::cmd_resized] == S::one){
		Conf::dHeight=rw.getSize().y;
		Conf::dWidth=rw.getSize().x;
		RESETMYGS();
		backgroundResize();
		dirty = true;
	}else if (msg.changes[S::cmd_review] == S::one) {
		dirty = true;
	} else if (msg.changes[S::cmd_cameracheck] == S::one) {
		cameraCheck();
	}

	if(!msg.changes[S::cmd_setmenuview].empty()){
		mainMenu.setSelected(msg.changes[S::cmd_setmenuview]);
	}

	if (msg.changes[S::cmd_next_wave] == S::zero)
		mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_next_wave].setVisible(false);
	else if (msg.changes[S::cmd_next_wave] == S::one)
		mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_next_wave].setVisible(true);

	if (msg.changes[S::cmd_pluswave] == S::one)
		++currentWave;

	bool moneytransfer = false;
	if (!msg.changes[S::cmd_money_minus].empty()) {
		int val = std::stoi(msg.changes[S::cmd_money_minus]);
		money -= std::abs(val);
		moneytransfer = true;
	} else if (!msg.changes[S::cmd_money_plus].empty()) {
		int val = std::stoi(msg.changes[S::cmd_money_plus]);
		money += std::abs(val);
		moneytransfer = true;
	}
	if (moneytransfer) {
		moneyHandle();
		if (panelManager.getMap()[S::panel_tower].isOpened()) {
			towerPanelHandle();
		}
	}

	if (!msg.changes[S::cmd_closepanel].empty()) {
		if (msg.changes[S::cmd_closepanel] == S::panel_all) {
			panelManager.closeAll();
		} else {
			panelManager.close(msg.changes[S::cmd_closepanel]);
		}
	} else if (!msg.changes[S::cmd_openpanel].empty()) {
		if (msg.changes[S::cmd_openpanel] == S::panel_tower) {
			towerPanelHandle();
		}else if(msg.changes[S::cmd_openpanel] == S::panel_build){
			moneyHandle();
		}else if(msg.changes[S::cmd_openpanel] == S::panel_targeting){
			targetPanelHandle();
		}
		panelManager.open(msg.changes[S::cmd_openpanel]);
	}

	if (msg.classname == S::class_sfeventbridge) {
		if (msg.changes[S::cmd_menuback] == S::one) {
			std::string s = mainMenu.getSelected()->getText();
			if (s == S::menu_main) {
				if (Conf::gameRun) {
					mainMenu.setSelected(S::menu_backtomaindialog);
				} else {
//					rw.close();
					LOGE("Should close");
				}
			} else if (s == S::menu_options || s == S::menu_newgame || s == S::menu_help || s == S::menu_backtomaindialog) {
				mainMenu.setSelected(S::menu_main);
			} else if (s == S::menu_graphics || s == S::menu_sound || s == S::menu_others) {
				mainMenu.setSelected(S::menu_options);
			} else if (s == S::menu_quickmatch || s == S::menu_campaign) {
				mainMenu.setSelected(S::menu_newgame);
			} else if (s == S::menu_howto || s == S::menu_authors) {
				mainMenu.setSelected(S::menu_help);
			}

		} else if (msg.changes[S::cmd_showmenu] == S::one) {
			Conf::gamePause = true;
			panelManager.closeAll();
			mainMenu.setSelected(S::menu_main);
		}
	}

#define BACKTO(n) if(ISCLICKED(S::btn_return)){mainMenu.setSelected(n);}

	if (msg.classname == S::class_simplebutton) {
		std::string s = msg.parentname;
		if (s == S::menu_gamegui) {
			if (msg.objectname == S::btn_zoomin && msg.changes[S::state_hover] == S::one) {
				map.zoom(-Conf::dtime * 333);
			} else if (msg.objectname == S::btn_zoomout
					&& msg.changes[S::state_hover] == S::one) {
				map.zoom(+Conf::dtime * 333);
			} else if (msg.objectname == S::btn_dbg && msg.changes[S::state_hover] == S::one) {
				//special debug button for various tests
				sf::sleep(sf::milliseconds(100));
			} else if (msg.objectname == S::btn_next_wave && msg.changes[S::state_clicked] == S::one) {
				map.nextWave();
			}
		} else if (s == S::menu_main) {
			if (ISCLICKED(S::btn_new_game)) {
				mainMenu.setSelected(S::menu_newgame);
			} else if (ISCLICKED(S::btn_options)) {
				mainMenu.setSelected(S::menu_options);
			} else if (ISCLICKED(S::btn_help)) {
				mainMenu.setSelected(S::menu_help);
			} else if (ISCLICKED(S::btn_continue)) {
				Conf::gamePause = false;
				mainMenu.setSelected(S::menu_gamegui);
			} else if (ISCLICKED(S::btn_exit_game)) {
				mainMenu.setSelected(S::menu_backtomaindialog);
			}
		} else if (s == S::menu_newgame) {
			if (ISCLICKED(S::btn_campaign)) {
				mainMenu.setSelected(S::menu_campaign);
			} else if (ISCLICKED(S::btn_quick_match)) {
				mainMenu.setSelected(S::menu_quickmatch);
			}
			BACKTO(S::menu_main);
		} else if (s == S::menu_campaign) {						///DEMO DEMO DEMO
			if (ISCLICKED(S::btn_demo)) {
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_new_game].setVisible(false);
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_continue].setVisible(true);
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_exit_game].setVisible(true);

				mainMenu.setSelected(S::menu_empty);
				loadedEnemies = 0;
				loading = true;
				initThread.launch();
			}
			BACKTO(S::menu_newgame);
		} else if (s == S::menu_quickmatch) {
			BACKTO(S::menu_newgame);
		} else if (s == S::menu_options) {
			if (ISCLICKED(S::btn_options_others)) {
				mainMenu.setSelected(S::menu_others);
			} else if (ISCLICKED(S::btn_options_graphics)) {
				mainMenu.setSelected(S::menu_graphics);
			} else if (ISCLICKED(S::btn_options_sound)) {
				mainMenu.setSelected(S::menu_sound);
			}
			BACKTO(S::menu_main);
		} else if (s == S::menu_others) {
			if (ISCLICKED(S::btn_change_lang)) {
				Lang::set2Next();
				std::string str = Lang::getSelected();
				str.resize(str.size()-1);
				mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_change_lang_cb].setText(str);
			} else if (ISCLICKED(S::btn_change_debug)) {
				if (Conf::debugEnable) {
					Conf::debugEnable = false;
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_debug_cb].setTexture(S::tex_unchecked);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_debug_cb].setText("");
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_dbg].setVisible(false);	//special dbg button
				} else {
					Conf::debugEnable = true;
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_debug_cb].setTexture(S::tex_checked);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_debug_cb].setText("X");
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_dbg].setVisible(true);	//special dbg button
				}
			} else if (ISCLICKED(S::btn_change_zoom_buttons)) {
				if (mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_zoomin].isVisible()) {
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_zoomin].setVisible(false);
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_zoomout].setVisible(false);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_zoom_buttons_cb].setTexture(S::tex_unchecked);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_zoom_buttons_cb].setText("");
				} else {
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_zoomin].setVisible(true);
					mainMenu.getMap()[S::menu_gamegui].getButtonMap()[S::btn_zoomout].setVisible(true);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_zoom_buttons_cb].setTexture(S::tex_checked);
					mainMenu.getMap()[S::menu_others].getButtonMap()[S::btn_zoom_buttons_cb].setText("X");
				}
			}
			BACKTO(S::menu_options);
		} else if (s == S::menu_graphics) {
			if (ISCLICKED(S::btn_gui_scale_reset)) {
				RESETMYGS();
				mainMenu.resetGsLabel();
			} else if (ISCLICKED(S::btn_gui_scale_plus)) {
				Conf::gs += 0.025f;
				if (Conf::gs > 10.0f) {
					Conf::gs = 10.0f;
				}
				mainMenu.resetGsLabel();
			} else if (ISCLICKED(S::btn_gui_scale_minus)) {
				Conf::gs -= 0.025f;
				if (Conf::gs <= 0.1f) {
					Conf::gs = 0.1f;
				}
				mainMenu.resetGsLabel();
			} else if(ISCLICKED(S::btn_texture_size)){
				if(Conf::textureDivisor==1){
					Conf::textureDivisor=2;
					mainMenu.getMap()[S::menu_graphics].getButtonMap()[S::btn_texture_size].setText(S::btn_texture_size_half);		
				}else{
					Conf::textureDivisor=1;
					mainMenu.getMap()[S::menu_graphics].getButtonMap()[S::btn_texture_size].setText(S::btn_texture_size_full);
				}
				Textures::init(true);
				
				sf::Texture *tex=&Textures::get(S::tex_background);
				sBackground.setTexture(tex);
				sBackground.setTextureRect(sf::IntRect(0,0,tex->getSize().x, tex->getSize().y));
				
				map.refreshAllTextures();
				mainMenu.refreshAllViewsTexture();
				panelManager.refreshAllPanelsTexture();
			}
			
			
			BACKTO(S::menu_options);
		} else if (s == S::menu_sound) {
			if (ISCLICKED(S::btn_menu_sound_plus)) {
				Conf::menuSoundVolume += 10.f;
				if (Conf::menuSoundVolume > 100.0f) {
					Conf::menuSoundVolume = 100.0f;
				}
				mainMenu.resetMSoundLabel();
			} else if (ISCLICKED(S::btn_menu_sound_minus)) {
				Conf::menuSoundVolume -= 10.f;
				if (Conf::menuSoundVolume <= 0.0f) {
					Conf::menuSoundVolume = 0.0f;
				}
				mainMenu.resetMSoundLabel();
			} else if (ISCLICKED(S::btn_game_sound_plus)) {
				Conf::gameSoundVolume += 10.f;
				if (Conf::gameSoundVolume > 100.0f) {
					Conf::gameSoundVolume = 100.0f;
				}
				mainMenu.resetGSoundLabel();
			} else if (ISCLICKED(S::btn_game_sound_minus)) {
				Conf::gameSoundVolume -= 10.f;
				if (Conf::gameSoundVolume <= 0.0f) {
					Conf::gameSoundVolume = 0.0f;
				}
				mainMenu.resetGSoundLabel();

			}
			BACKTO(S::menu_options);
		} else if (s == S::menu_help) {
			if (ISCLICKED(S::btn_authors)) {
				mainMenu.setSelected(S::menu_authors);
			} else if (ISCLICKED(S::btn_howto)) {
				mainMenu.setSelected(S::menu_howto);
			}
			BACKTO(S::menu_main);
		} else if (s == S::menu_howto) {
			BACKTO(S::menu_help);
		} else if (s == S::menu_authors) {
			BACKTO(S::menu_help);
		} else if (s == S::menu_backtomaindialog) {
			if (ISCLICKED(S::btn_yes)) {
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_new_game].setVisible(true);
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_continue].setVisible(false);
				mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_exit_game].setVisible(false);
				mainMenu.setSelected(S::menu_main);

				Conf::gamePause = false;
				Conf::gameRun = false;
				backgroundEnable = true;
				time = 0.f;
			} else if (ISCLICKED(S::btn_no)) {
				mainMenu.setSelected(S::menu_main);
			}
			BACKTO(S::menu_main);
		}
	}

	if (msg.classname == S::class_base) {
		if (!msg.changes[S::state_basehp].empty()) {
			baseHP -= std::stoi(msg.changes[S::state_basehp]);
			if (baseHP < 0)
				baseHP = 0;
		}
		if (baseHP <= 0 && !baseDestroy) {
			panelManager.closeAll();
			baseDestroy = true;
			startBaseDestroyTime = Conf::clock.getElapsedTime().asSeconds();
		}
	} else if (msg.parentname == S::menu_basedestroydialog) {
		if (ISCLICKED(S::btn_ok)){
			time = 0.0f;
			mainMenu.setSelected(S::menu_main);
			Conf::gamePause = false;

			Conf::gameRun = false;
			mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_new_game].setVisible(true);
			mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_continue].setVisible(false);
			mainMenu.getMap()[S::menu_main].getButtonMap()[S::btn_exit_game].setVisible(false);
			backgroundEnable = true;
			map.getBase().clearDmg();
		}
	}
}
void Game::dirtyCheck() {
	LOGF("Game::dirtyCheck");

	if (dirty) {
		dirty = false;
		review();
	}
}
void Game::drawShadow(sf::Text &t, float shift, sf::Color c1, sf::Color c2){
	sf::Color initCol=t.getFillColor();

	t.setFillColor(c1);
	rw.draw(t);

	t.move(2 * shift * Conf::zm * Conf::gs, 2 * Conf::zm * Conf::gs);
	t.setFillColor(c2);
	rw.draw(t);

	t.setFillColor(initCol);
	t.move(-shift * Conf::zm * Conf::gs, -shift * Conf::zm * Conf::gs);
	rw.draw(t);
}
void Game::drawStatusBar() {
	LOGF("Game::drawStatusBar");

	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(255, 255, 255, 200));
	rs.setPosition(rw.mapPixelToCoords(sf::Vector2i(0, 0)));
	rs.setSize(sf::Vector2f(Conf::vw.getSize().x, 100 * Conf::zm * Conf::gs));
	rs.setTexture(&Textures::get(S::tex_bar));
	rw.draw(rs);

	sf::Text m;

	m.setFont(Conf::fMono);
	m.setCharacterSize(32);
	m.setScale(Conf::zm * Conf::gs, Conf::zm * Conf::gs);
		//Money text
	sf::String str = l("money");
	m.setString(str);
	m.setPosition(rs.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move((rs.getSize().x * 0.55), 10 * Conf::zm * Conf::gs);
	m.setFillColor(sf::Color(0, 128, 0, 255));
	drawShadow(m,1,sf::Color::Black, sf::Color::Yellow);

		//Money ammount
	str = std::to_string(money);
	m.setString(str);
	m.setPosition(m.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move(0, 40 * Conf::zm * Conf::gs);
	drawShadow(m,1,sf::Color::Black, sf::Color::Yellow);

		//Base text
	m.setPosition(rs.getPosition());
	str = l(S::state_basehp);
	m.setString(str);
	m.setPosition(rs.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move((rs.getSize().x * 0.80), 10 * Conf::zm * Conf::gs);
	m.setFillColor(sf::Color(0, 128, 255, 255));
	drawShadow(m,1,sf::Color::Black, sf::Color::Cyan);

		//Base hp bar
	sf::RectangleShape baseBar;
	baseBar.setSize(sf::Vector2f(400.f * Conf::zm * Conf::gs,40.f * Conf::zm * Conf::gs));
	baseBar.setOrigin(baseBar.getLocalBounds().width / 2, baseBar.getLocalBounds().height / 2);
	baseBar.setPosition(m.getPosition());
	baseBar.move(0, 50 * Conf::zm * Conf::gs);
	baseBar.setOutlineThickness(6.f * Conf::zm * Conf::gs);
	baseBar.setOutlineColor(sf::Color::Black);
	baseBar.setFillColor(sf::Color::Transparent);
	rw.draw(baseBar);
	baseBar.setSize(sf::Vector2f(400.f * (baseHP * 1.0f) / (baseMaxHP * 1.0f) * Conf::zm	* Conf::gs, 40.f * Conf::zm * Conf::gs));
	baseBar.setOutlineColor(sf::Color::Transparent);
	baseBar.setTexture(&Textures::get(S::tex_blend));
	baseBar.setFillColor(sf::Color(((baseMaxHP * 1.f - baseHP * 1.f) / baseMaxHP * 1.f) * 255,0, 255, 160));
	rw.draw(baseBar);
		//Base hp ammount
	str = std::to_string(baseHP);
	m.setString(str);
	m.setCharacterSize(24);
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height * 0.75);
	m.setPosition(baseBar.getPosition());
	m.setFillColor(sf::Color::Cyan);
	drawShadow(m,1,sf::Color::Black, sf::Color::White);

		//Time text
	str = l("time");
	m.setString(str);
	m.setCharacterSize(32);
	m.setPosition(rs.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move((rs.getSize().x * 0.35), 10 * Conf::zm * Conf::gs);
	m.setFillColor(sf::Color::Yellow);
	drawShadow(m,1,sf::Color::Black, sf::Color::White);

		//Time ammount
	if (Conf::gameRun && !Conf::gamePause
		/*&& (CLOCKASMS - Conf::dtime >= 1.0f)*/) {
		time += Conf::dtime;
	}
	str = std::to_string((int) time);
	m.setString(str + "s");
	m.setPosition(m.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move(0, 40 * Conf::zm * Conf::gs);
	drawShadow(m,1,sf::Color::Black, sf::Color::White);

	//Waves
	str = l(S::state_wave);
	m.setString(str);
	m.setCharacterSize(32);
	m.setPosition(rs.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move((rs.getSize().x * 0.45), 10 * Conf::zm * Conf::gs);
	m.setFillColor(sf::Color::Cyan);
	drawShadow(m, 1, sf::Color::Black, sf::Color::White);

	m.move(0, 40 * Conf::gs * Conf::zm);
	str = std::to_string(currentWave) + "/" + std::to_string(maxWaves);
	m.setString(str);
	drawShadow(m, 1, sf::Color::Black, sf::Color::White);

		//Enemies text
	str = l("killedenemies");
	m.setString(str);
	m.setPosition(rs.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move((rs.getSize().x *0.15), 10 * Conf::zm * Conf::gs);
	m.setFillColor(sf::Color(200, 0, 0, 255));
	drawShadow(m,1,sf::Color::Black, sf::Color::White);

		//Enemies ammount
	str = std::to_string(map.enemiesKilled());
	m.setString(str);
	m.setPosition(m.getPosition());
	m.setOrigin(m.getLocalBounds().width / 2, m.getLocalBounds().height / 2);
	m.move(0, 40 * Conf::zm * Conf::gs);
	drawShadow(m,1,sf::Color::Black, sf::Color::White);
}
void Game::destroyBase() {
	LOGF("Game::destroyBase");

	float step = 20.f*std::sqrt((Conf::clock.getElapsedTime().asSeconds() - startBaseDestroyTime) * 6);
	sf::Vector2f currentPos = rw.getView().getCenter();
	sf::Vector2f basePos = map.getBase().getPosition();

	float dx = basePos.x - currentPos.x;

	if (dx == 0) {
		baseDestroy = false;
		Conf::gamePause = true;
		mainMenu.setSelected(S::menu_basedestroydialog);
		return;
	}
	float m = (basePos.y - currentPos.y) / dx;
	float b = currentPos.y - (m * currentPos.x);

	float x;
	if (currentPos.x < basePos.x) {
		if (basePos.x - currentPos.x < step)
			x = basePos.x;
		else
			x = currentPos.x + step;
	} else {
		if (currentPos.x - basePos.x < step)
			x = basePos.x;
		else
			x = currentPos.x - step;
	}
	float y = m * x + b;
	Conf::vw.setCenter(sf::Vector2f(x, y));
	rw.setView(Conf::vw);
	map.updateVisibleBounds(rw);
}
void Game::initGame() {
	LOGF("Game::initGame");

	Conf::newzoom = 1 / Conf::gs;
	if(Conf::debugEnable){
		baseHP = money = 999999;
	}else{
		baseHP = baseMaxHP;
		money = 1000;
	}

	currentWave = 1;

	panelManager.closeAll();
	review();

	std::vector<Enemy*> ve;

	Path *p = &map.getPath();
	loadedEnemies = 0;
	enemyCount = 50;

	for (int i = 0; i < enemyCount; ++i) {
		if (i > enemyCount - 15)
			ve.push_back(new LightHoverCraft(p));
		else {
			if (i % 2 == 0)
				ve.push_back(new LightHoverCraft(p));
			else
				ve.push_back(new LightBomber(p));
		}
		(*ve.rbegin())->addListener(&map);
//		(*ve.rbegin())->setEnabled(true); //Only for instant enabling tests
		++loadedEnemies;
	}
	map.spawningInit(enemyCount);
	map.setEnemies(ve);

	loading = false;
	Conf::gamePause = false;
	Conf::gameRun = true;
	baseDestroy = false;
	backgroundEnable = false;
	mainMenu.setSelected(S::menu_gamegui);

//	initThread.terminate();
}
void Game::drawLoadingScreen() {
	LOGF("Game::drawLoadingScreen");

//	Conf::rwmutex.lock();
	sf::Text loadingText;
	loadingText.setString(Lang::translate("loading"));
	loadingText.setFont(Conf::fSansation);
	loadingText.setCharacterSize(100);
	loadingText.setPosition(rw.mapPixelToCoords(sf::Vector2i(0, 0)));
	sf::Vector2i tmp;
	tmp.x = Conf::dWidth - loadingText.getLocalBounds().width- Conf::dWidth * 0.05;
	tmp.y = Conf::dHeight * 0.9f - 120;
	loadingText.setPosition(rw.mapPixelToCoords(tmp));
	loadingText.setScale(Conf::zm, Conf::zm);
	loadingText.setFillColor(sf::Color::White);
	drawShadow(loadingText,2.0f, sf::Color::White, sf::Color::Black);

	sf::RectangleShape rs;
	rs.setPosition(rw.mapPixelToCoords(sf::Vector2i(0, Conf::dHeight * 0.9)));
	rs.setTexture(&Textures::get(S::tex_blend));
	rs.setSize(	sf::Vector2f(Conf::dWidth * ((loadedEnemies * 1.f) / (enemyCount * 1.f)),50.f));
	rs.setScale(Conf::zm, Conf::zm);
	rs.setFillColor(sf::Color::Red);
	rw.draw(rs);
//	Conf::rwmutex.unlock();
}
void Game::backgroundResize(){
	sf::Vector2u ts = sBackground.getTexture()->getSize();
	float ratio= 1.0f * Conf::dHeight / ts.y;
	sBackground.setSize(sf::Vector2f(ts.x * ratio, ts.y * ratio));
	if(sBackground.getGlobalBounds().width < Conf::dWidth){
		ratio= 1.0f * Conf::dWidth / ts.x;
		sBackground.setSize(sf::Vector2f(ts.x * ratio, ts.y * ratio));
	}
}
