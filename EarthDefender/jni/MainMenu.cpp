#include "MainMenu.hpp"
#include "log.hpp"
#include "Conf.hpp"
#include "Gestures.hpp"

MainMenu::MainMenu():
	selected(NULL),
	firstPos(0.f,-0.20f),
	moveStep(0.f, 0.15f),
	miniStep(0.f, 0.1),
	defBtnSiz(400,100),
	defCbSiz(100,100),
	bigBtnSiz(800,200),
	minBtnSiz(200,50),
	texS(90.0f, 90.0f),
	moveRight(0.22f,0.0f),
	moveLeft(-0.22f,0.0f),
	defTextShift(32.f,32.f),
	cbTextShift(0.0f,-8.0f),
	defFontSize(32),
	bigFontSize(48),
	minFontSize(24)
{
	selected=&mvmap[S::menu_main];

	mvmap[S::menu_main].setText(S::menu_main);
	mvmap[S::menu_options].setText(S::menu_options);
	mvmap[S::menu_newgame].setText(S::menu_newgame);
	mvmap[S::menu_campaign].setText(S::menu_campaign);
	mvmap[S::menu_graphics].setText(S::menu_graphics);
	mvmap[S::menu_sound].setText(S::menu_sound);
	mvmap[S::menu_about].setText(S::menu_about);
	mvmap[S::menu_help].setText(S::menu_help);
	mvmap[S::menu_others].setText(S::menu_others);
	mvmap[S::menu_authors].setText(S::menu_authors);
	mvmap[S::menu_howto].setText(S::menu_howto);
	mvmap[S::menu_quickmatch].setText(S::menu_quickmatch);
	mvmap[S::menu_backtomaindialog].setText(S::menu_backtomaindialog);
	mvmap[S::menu_gamegui].setText(S::menu_gamegui);
	mvmap[S::menu_basedestroydialog].setText(S::menu_basedestroydialog);

#define ADDRET(menuview)  btn.setSound(S::snd_s1); btn.move(moveStep); btn.setText(S::btn_return); menuview.setButton(btn); btn.setSound(S::snd_s2);
#define ADDRETNM(menuview) btn.setSound(S::snd_s1); btn.setText(S::btn_return); menuview.setButton(btn); btn.setSound(S::snd_s2);

	sf::Vector2f tmpsiz;
	std::string str;
	SimpleButton btn;

//Game gui view
	btn.setParent(S::menu_gamegui);

	btn.setPositionReference(vprBottom,hprLeft);
	btn.setTextSize(bigFontSize);
	btn.setPosition(sf::Vector2f(0.05f,-0.05f));

	btn.setTexture(S::tex_button);
	btn.setText(S::btn_next_wave);
	btn.setSize(sf::Vector2f(400.f, 100.f));
	mvmap[S::menu_gamegui].setButton(btn);

	btn.move(moveStep,-1.0);
	btn.setTextShift(cbTextShift);
	btn.setText("-");
	btn.setSize(defCbSiz);
	btn.setTexture(S::tex_unchecked);
	mvmap[S::menu_gamegui].setButton(btn,S::btn_zoomout);

	btn.move(moveStep,-1.0);
	btn.setText("+");
	mvmap[S::menu_gamegui].setButton(btn,S::btn_zoomin);

	btn.move(moveRight,0.4);
	btn.setText(S::btn_dbg);
	if (!Conf::debugEnable)
		btn.setVisible(false);
	mvmap[S::menu_gamegui].setButton(btn,S::btn_dbg);
	btn.setVisible(true);

	btn.setPositionReference(vprCenter,hprCenter);
//Game gui view end
//Main view
	btn.setParent(S::menu_main);

	btn.setText(S::btn_new_game);
	btn.setTexture(S::tex_button);
	btn.setSound(S::snd_s2);
	btn.setTextShift(vzero);
	btn.setTextSize(defFontSize);
	btn.setPosition(firstPos);
	btn.setSize(defBtnSiz);
	mvmap[S::menu_main].setButton(btn);

	btn.setText(S::btn_continue);
	btn.move(-miniStep);
	btn.setVisible(false);
	mvmap[S::menu_main].setButton(btn);
	btn.setVisible(true);
	btn.move(miniStep);

	btn.move(moveStep);
	btn.setText(S::menu_options);
	mvmap[S::menu_main].setButton(btn);

	btn.move(moveStep);
	btn.setText(S::menu_help);
	mvmap[S::menu_main].setButton(btn);

	btn.move(moveStep);
	btn.setText(S::btn_exit_game);
	btn.setVisible(false);
	mvmap[S::menu_main].setButton(btn);
	btn.setVisible(true);

//Newgame view
		btn.setParent(S::menu_newgame);

		btn.setPosition(firstPos);
		btn.setText(S::menu_campaign);
		mvmap[S::menu_newgame].setButton(btn);

		btn.move(moveStep);
		btn.setText(S::btn_quick_match);
		mvmap[S::menu_newgame].setButton(btn);

		ADDRET(mvmap[S::menu_newgame]);
	//Campaign view
			btn.setParent(S::menu_campaign);

			btn.setPosition(firstPos);
			btn.setText(S::btn_demo);
			mvmap[S::menu_campaign].setButton(btn,S::btn_demo);

			ADDRET(mvmap[S::menu_campaign]);
	//Campaign view end

	//Quick match view
			btn.setParent(S::menu_quickmatch);

			btn.setPosition(firstPos);
			ADDRET(mvmap[S::menu_quickmatch]);
	//Quick match view end
//Newgame view end

//Options view
		btn.setParent(S::menu_options);

		btn.setPosition(firstPos);
		btn.setText(S::btn_options_others);
		mvmap[S::menu_options].setButton(btn);

		btn.move(moveStep);
		btn.setText(S::btn_options_graphics);
		mvmap[S::menu_options].setButton(btn);

		btn.move(moveStep);
		btn.setText(S::btn_options_sound);
		mvmap[S::menu_options].setButton(btn);

		ADDRET(mvmap[S::menu_options]);

	//Others option view
			btn.setParent(S::menu_others);

			btn.setSound(S::snd_s3);
			btn.setPosition(firstPos);
			btn.setText(S::btn_change_lang);
			mvmap[S::menu_others].setButton(btn);

			btn.move(moveRight);
			btn.setSize(defCbSiz);
			btn.setEnabled(false);
			btn.setTexture(S::tex_squarebutton);
			str = Lang::getSelected();
			str.resize(str.size()-1);
			btn.setText(str);
			mvmap[S::menu_others].setButton(btn,S::btn_change_lang_cb);
			btn.setEnabled(true);
			btn.setTexture(S::tex_button);
			btn.move(moveLeft);
			btn.setSize(defBtnSiz);

			btn.move(moveStep);
			btn.setText(S::btn_change_zoom_buttons);
			mvmap[S::menu_others].setButton(btn);

			btn.setTextSize(bigFontSize);
			btn.setText("X");
			btn.setTexture(S::tex_checked);
			btn.move(moveRight);
			btn.setSize(defCbSiz);
			btn.setEnabled(false);
			mvmap[S::menu_others].setButton(btn,S::btn_zoom_buttons_cb);
			btn.setEnabled(true);
			btn.setTextSize(defFontSize);
			btn.setSize(defBtnSiz);
			btn.setTexture(S::tex_button);
			btn.move(-moveRight);

			btn.move(moveStep);
			btn.setText(S::btn_change_debug);
			mvmap[S::menu_others].setButton(btn);

			btn.setTextSize(bigFontSize);
			if(Conf::debugEnable){
				btn.setTexture(S::tex_checked);
				btn.setText("X");
			}
			else{
				btn.setTexture(S::tex_unchecked);
				btn.setText("");
			}

			btn.move(moveRight);
			btn.setSize(defCbSiz);
			btn.setEnabled(false);
			mvmap[S::menu_others].setButton(btn,S::btn_debug_cb);
			btn.setEnabled(true);
			btn.setTextSize(defFontSize);
			btn.setSize(defBtnSiz);
			btn.setTexture(S::tex_button);
			btn.move(-moveRight);

			ADDRET(mvmap[S::menu_others]);
	//Others option view end

	//Graphics option view
			btn.setParent(S::menu_graphics);

			btn.setPosition(moveStep);
			//btn.move(moveStep);

			btn.setSound(S::snd_s3);
			btn.setSize(bigBtnSiz);
			btn.setTextSize(bigFontSize);
			btn.setPositionReference(vprTop,hprCenter);
			btn.setText(S::btn_gui_scale_reset);
			mvmap[S::menu_graphics].setButton(btn);

			btn.setSize(defCbSiz);
			btn.setTextShift(cbTextShift);
			btn.setTexture(S::tex_unchecked);
			btn.move(moveStep,2.0f);
			btn.move(moveRight);
			btn.setText("+");
			mvmap[S::menu_graphics].setButton(btn,S::btn_gui_scale_plus);
			btn.move(moveRight,-2.0f);

			btn.setText("-");
			mvmap[S::menu_graphics].setButton(btn,S::btn_gui_scale_minus);

			btn.move(moveRight);
			btn.setSize(defBtnSiz);
			btn.setTextSize(defFontSize);
			btn.setTextShift(vzero);
			btn.setTexture(S::tex_color_black);
			btn.setEnabled(false);
			mvmap[S::menu_graphics].setButton(btn,S::btn_gui_scale_label);
			resetGsLabel();

			btn.setTexture(S::tex_button);
			btn.setEnabled(true);
			btn.setSize(defBtnSiz);

			btn.move(moveStep);
			btn.setText(S::btn_texture_size_full);
//				btn.setEnabled(false);
			mvmap[S::menu_graphics].setButton(btn,S::btn_texture_size);
//				btn.setEnabled(true);

			ADDRET(mvmap[S::menu_graphics]);
			btn.setPositionReference(vprCenter,hprCenter);
	//Graphics option view end

	//Sound options view
			btn.setParent(S::menu_sound);

			btn.setSound(S::snd_s3);
			btn.setPosition(firstPos);

			btn.setTextSize(minFontSize);
			btn.setSize(minBtnSiz);
			btn.setText(S::btn_menu_volume);
			btn.setTexture(S::tex_color_lgray);
			btn.setEnabled(false);
			mvmap[S::menu_sound].setButton(btn);
			btn.setEnabled(true);

			btn.move(miniStep);
			btn.move(moveRight);
			btn.setTextSize(bigFontSize);
			btn.setSize(defCbSiz);
			btn.setTextShift(cbTextShift);
			btn.setTexture(S::tex_unchecked);
			btn.setText("+");
			mvmap[S::menu_sound].setButton(btn,S::btn_menu_sound_plus);
			btn.move(moveRight,-2.0f);

			btn.setTexture(S::tex_unchecked);
			btn.setText("-");
			mvmap[S::menu_sound].setButton(btn,S::btn_menu_sound_minus);

			btn.move(moveRight);
			btn.setSize(defBtnSiz);
			btn.setTexture(S::tex_color_black);
			btn.setEnabled(false);
			mvmap[S::menu_sound].setButton(btn,S::btn_menu_sound_label);
			resetMSoundLabel();

			btn.move(moveStep);
			btn.setSize(minBtnSiz);
			btn.setTextSize(minFontSize);
			btn.setTextShift(vzero);
			btn.setText(S::btn_game_volume);
			btn.setTexture(S::tex_color_lgray);
			btn.setEnabled(false);
			mvmap[S::menu_sound].setButton(btn);
			btn.setEnabled(true);

			btn.move(miniStep);
			btn.setTextSize(bigFontSize);
			btn.setSize(defCbSiz);
			btn.setTextShift(cbTextShift);
			btn.setTexture(S::tex_unchecked);
			btn.move(moveRight);
			btn.setText("+");
			mvmap[S::menu_sound].setButton(btn,S::btn_game_sound_plus);
			btn.move(moveRight,-2.0f);

			btn.setText("-");
			mvmap[S::menu_sound].setButton(btn,S::btn_game_sound_minus);

			btn.move(moveRight);
			btn.setSize(defBtnSiz);
			btn.setTextShift(vzero);
			btn.setTexture(S::tex_color_black);
			btn.setEnabled(false);
			mvmap[S::menu_sound].setButton(btn,S::btn_game_sound_label);
			resetGSoundLabel();

			btn.setEnabled(true);
			btn.setTexture(S::tex_button);
			btn.setTextSize(defFontSize);
			btn.setTextShift(vzero);
			ADDRET(mvmap[S::menu_sound]);
	//Sound options view end
//Options view end

//Help view
		btn.setParent(S::menu_help);

		btn.setPosition(firstPos);
		btn.setText(S::btn_howto);
		mvmap[S::menu_help].setButton(btn);

		btn.move(moveStep);
		btn.setText(S::menu_authors);
		mvmap[S::menu_help].setButton(btn);

		ADDRET(mvmap[S::menu_help]);
	//HowTo view
			btn.setParent(S::menu_howto);

			btn.setPosition(moveStep);
			btn.setText(S::btn_howto_info);
			btn.setTextCenter(false);
			btn.setEnabled(false);
			btn.setPositionReference(vprTop,hprCenter);
			btn.setTexture(S::tex_color_black);
			btn.setSize(sf::Vector2f(800,400));
			btn.setTextShift(texS);
			mvmap[S::menu_howto].setButton(btn);

			btn.setTextShift(vzero);
			btn.setPositionReference(vprBottom,hprCenter);
			btn.setEnabled(true);
			btn.setTextCenter(true);
			btn.setTexture(S::tex_button);
			btn.setSize(defBtnSiz);
			btn.setPosition(-moveStep);

			ADDRETNM(mvmap[S::menu_howto]);
			btn.setPositionReference(vprCenter,hprCenter);
	//HowTo view end

	//Authors view
			btn.setParent(S::menu_authors);

			btn.setPosition(moveStep);
			btn.setText(S::btn_authors_info);
			btn.setTextCenter(false);
			btn.setEnabled(false);
			btn.setPositionReference(vprTop,hprCenter);
			btn.setTexture(S::tex_color_black);
			btn.setSize(sf::Vector2f(800,400));
			btn.setTextShift(texS);
			mvmap[S::menu_authors].setButton(btn);

			btn.setTextShift(vzero);
			btn.setEnabled(true);
			btn.setTextCenter(true);
			btn.setTexture(S::tex_button);
			btn.setSize(defBtnSiz);
			btn.setPosition(-moveStep);

			btn.setPositionReference(vprBottom,hprCenter);

			ADDRETNM(mvmap[S::menu_authors]);
			btn.setPositionReference(vprCenter,hprCenter);
	//Authors view end

//Help view end

//Back to main dialog
	btn.setParent(S::menu_backtomaindialog);

	btn.setPositionReference(vprTop,hprCenter);

	btn.setPosition(moveStep);
	btn.setTextSize(bigFontSize);
	btn.setText(S::btn_exit_game_info);
	btn.setTextCenter(false);
	btn.setEnabled(false);
	btn.setTexture(S::tex_color_black);
	btn.setSize(sf::Vector2f(800,400));
	btn.setTextShift(defTextShift);
	mvmap[S::menu_backtomaindialog].setButton(btn);

	btn.setPositionReference(vprBottom,hprCenter);

	btn.setPosition(-moveStep);
	btn.move(moveLeft);
	btn.setTexture(S::tex_button);
	btn.setTextSize(defFontSize);
	btn.setSize(defBtnSiz);
	btn.setTextShift(vzero);
	btn.setTextCenter(true);
	btn.setEnabled(true);
	btn.setText(S::btn_yes);
	mvmap[S::menu_backtomaindialog].setButton(btn);

	btn.move(moveRight,2.0f);
	btn.setText(S::btn_no);
	mvmap[S::menu_backtomaindialog].setButton(btn);

	btn.setPositionReference(vprCenter,hprCenter);
//Back to main dialog end
//Base destroy dialog
	btn.setParent(S::menu_basedestroydialog);

	btn.setPositionReference(vprTop,hprCenter);

	btn.setPosition(moveStep);
	btn.setTextSize(bigFontSize);
	btn.setText(S::btn_base_destroy);
	btn.setTextCenter(false);
	btn.setEnabled(false);
	btn.setTexture(S::tex_color_black);
	btn.setSize(sf::Vector2f(800,400));
	btn.setTextShift(defTextShift);
	mvmap[S::menu_basedestroydialog].setButton(btn);

	btn.setPositionReference(vprBottom,hprCenter);

	btn.setPosition(-moveStep);
	btn.setTexture(S::tex_button);
	btn.setTextSize(defFontSize);
	btn.setSize(defBtnSiz);
	btn.setTextShift(vzero);
	btn.setTextCenter(true);
	btn.setEnabled(true);
	btn.setText(S::btn_ok);
	mvmap[S::menu_basedestroydialog].setButton(btn);

	//btn.move(moveRight,2.0f);
	//btn.setText(S::btn_no);
	//mvmap[S::menu_basedestroydialog].setButton(btn);

	btn.setPositionReference(vprCenter,hprCenter);
//Base destroy dialog end

//Main view end
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	target.draw(*selected,states);
}
void MainMenu::update(sf::RenderWindow &rw){
	LOGF("MainMenu::update");
	selected->update(rw);
}
