#include "PanelManager.hpp"
#include "Gatling.hpp"
#include "Coil.hpp"
#include "RocketLauncher.hpp"
#include "LightCannon.hpp"

PanelManager::PanelManager():
	moveStep(0.f, 0.35f),
	moveRight(0.5f, 0.0f)
{
	mpanels[S::panel_build].setText(S::panel_build);
	mpanels[S::panel_build].setTextSize(44);
	mpanels[S::panel_build].setSize(sf::Vector2f(400.0f,800.0f));
	mpanels[S::panel_build].setScrollStop(100.0f);
	mpanels[S::panel_build].setPositionReference(vprTop, hprRight);

	mpanels[S::panel_tower].setText(S::btn_tower_info);
	mpanels[S::panel_tower].setTextSize(44);
	mpanels[S::panel_tower].setSize(sf::Vector2f(400.0f,800.0f));
	mpanels[S::panel_tower].setScrollStop(0.0f);
	mpanels[S::panel_tower].setPositionReference(vprTop, hprRight);

	mpanels[S::panel_targeting].setText(S::panel_targeting);
	mpanels[S::panel_targeting].setTextSize(30);
	mpanels[S::panel_targeting].setTextCenter(false);
	mpanels[S::panel_targeting].setTextShift(sf::Vector2f(20.f,20.f));
	mpanels[S::panel_targeting].setSize(sf::Vector2f(300.0f,800.0f));
	mpanels[S::panel_targeting].setScrollStop(0.0f);
	mpanels[S::panel_targeting].setPositionReference(vprTop, hprLeft);

	SimpleButton btn;


	//targeting panel
	btn.setParent(S::panel_targeting);
	btn.setTexture(S::tex_squarebutton);
	btn.setTextSize(24);
	btn.setPositionReference(vprTop, hprLeft);
	btn.setScreenReference(false);
	btn.setPercentPosition(false);
	btn.setPosition(sf::Vector2f(240.f, 0.f));
	btn.setName(S::btn_close);
	btn.setText("<<\n<<");
	btn.setSize(sf::Vector2f(120.0f, 120.0f));
	mpanels[S::panel_targeting].setSpecialButton(btn);

	btn.setPercentPosition(true);
	btn.setTexture(S::tex_unchecked);

	btn.setPosition(sf::Vector2f(0.f, 0.20f));
	btn.setPositionReference(vprTop, hprCenter);
	btn.setSize(sf::Vector2f(165.0f, 165.0f));
	btn.setText(S::btn_target_first);
	mpanels[S::panel_targeting].setButton(btn);

	btn.move(moveStep, 0.666f);
	btn.setPositionReference(vprTop, hprCenter);
	btn.setSize(sf::Vector2f(165.0f, 165.0f));
	btn.setText(S::btn_target_last);
	mpanels[S::panel_targeting].setButton(btn);

	btn.move(moveStep, 0.666f);
	btn.setPositionReference(vprTop, hprCenter);
	btn.setSize(sf::Vector2f(165.0f, 165.0f));
	btn.setText(S::btn_target_nearest);
	mpanels[S::panel_targeting].setButton(btn);

	//targeting panel end

	//build panel
	btn.setParent(S::panel_build);
	btn.setTexture(S::tex_squarebutton);
	btn.setTextSize(30);
	btn.setPositionReference(vprTop, hprLeft);
	btn.setScreenReference(false);
	btn.setPercentPosition(false);
	btn.setPosition(sf::Vector2f(-60.f, 0.f));
	btn.setName(S::btn_close);
	btn.setText(">>\n>>");
	btn.setSize(sf::Vector2f(120.0f, 120.0f));
	mpanels[S::panel_build].setSpecialButton(btn);

	btn.setPercentPosition(true);
	btn.setText("");
	btn.setTextCenter(false);
	btn.setTextShift(sf::Vector2f(20.0f,20.0f));
	btn.setTextSize(36);

	btn.setPosition(sf::Vector2f(-0.25f, 0.20f));
	btn.setPositionReference(vprTop, hprCenter);
	btn.setSize(sf::Vector2f(165.0f, 165.0f));
	btn.setImageTexture(S::tex_tower_lightcannon_1);
	btn.setImageTextureRect(sf::IntRect(0,0,LightCannon::frameW,LightCannon::frameH));
	btn.setImageScale(0.9);
	mpanels[S::panel_build].setButton(btn,S::tower_lightcannon);

	btn.move(moveRight);
	btn.setImageTexture(S::tex_tower_gatling_1);
	btn.setImageTextureRect(sf::IntRect(0,0,Gatling::frameW,Gatling::frameH));
	btn.setImageScale(0.8);
	mpanels[S::panel_build].setButton(btn,S::tower_gatling);

	btn.move(moveRight, -1.0f);
	btn.move(moveStep, 0.666f);
	btn.setImageTexture(S::tex_tower_coil_1);
	btn.setImageTextureRect(sf::IntRect(0,0,Coil::frameW,Coil::frameH));
	btn.setImageScale(0.8);
	mpanels[S::panel_build].setButton(btn,S::tower_coil);

	btn.move(moveRight);
	btn.setImageTexture(S::tex_tower_rocketlauncher_1);
	btn.setImageTextureRect(sf::IntRect(0,0,RocketLauncher::frameW,RocketLauncher::frameH));
	btn.setImageScale(0.7);
	mpanels[S::panel_build].setButton(btn, S::tower_rocketlauncher);

	btn.setImageScale(1.0);
	btn.setImageTexture("");
	btn.setTextCenter(true);
	btn.setTextShift(vzero);
	//build panel end

	//tower panel
	btn.setParent(S::panel_tower);

	btn.setTexture(S::tex_squarebutton);
	btn.setTextSize(30);
	btn.setPositionReference(vprTop, hprLeft);
	btn.setScreenReference(false);
	btn.setPercentPosition(false);
	btn.setPosition(sf::Vector2f(-60.f, 0.f));
	btn.setName(S::btn_close);
	btn.setText(">>\n>>");
	btn.setSize(sf::Vector2f(120.0f, 120.0f));
	mpanels[S::panel_tower].setSpecialButton(btn);

	btn.setPercentPosition(true);
	btn.setPositionReference(vprTop, hprCenter);
	btn.setPosition(sf::Vector2f(0.0f, 0.12f));
	btn.setEnabled(false);
	btn.setTexture(S::tex_color_lgray);
	btn.setImageTextureRect(sf::IntRect(0,0,1,1));
	btn.setText("information");
	btn.setSize(sf::Vector2f(160.0f, 60.0f));
	mpanels[S::panel_tower].setButton(btn,S::btn_info_label);
	btn.move(sf::Vector2f(0.f,0.08f));

	btn.setTextParse(false);
	btn.setTexture(S::tex_color_dgray);
	btn.setTextParse(true);
	btn.setTextCenter(false);
	btn.setSize(sf::Vector2f(360.0f, 180.0f));
	btn.setTextShift(sf::Vector2f(20.f,20.f));
	mpanels[S::panel_tower].setButton(btn,S::btn_info);

	btn.setTextShift(vzero);
	btn.setEnabled(true);
	btn.setTextParse(true);
	btn.setTextCenter(true);

	btn.move(sf::Vector2f(0.0f, 0.25f));
	btn.setText(S::tex_upgrade);
	btn.setTexture(S::tex_button);
	btn.setSize(sf::Vector2f(380.0f, 95.0f));
	btn.setImageTexture(S::tex_upgrade);
	btn.setImageTextureRect(sf::IntRect(0,0,512/Conf::textureDivisor,161/Conf::textureDivisor));
	btn.setTextColor(sf::Color::Green);
	btn.setTextSize(36);
	mpanels[S::panel_tower].setButton(btn,S::tex_upgrade);

	btn.setTexture(S::tex_squarebutton);
	btn.move(sf::Vector2f(0.0f, 0.15f));
	btn.setText(S::btn_sell);
	btn.setSize(sf::Vector2f(200.0f, 200.0f));
	btn.setImageTexture(S::btn_sell);
	btn.setImageTextureRect(sf::IntRect(0,0,256/Conf::textureDivisor,256/Conf::textureDivisor));
	btn.setTextColor(sf::Color::Yellow);
	btn.setTextSize(36);
	mpanels[S::panel_tower].setButton(btn,S::btn_sell);
	//tower panel end
}


void PanelManager::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	for(const auto &p: mpanels){
		target.draw(p.second, states);
	}
}
void PanelManager::update(sf::RenderWindow &rw){
	LOGF("PanelManager::update");
	for(auto &p: mpanels){
		p.second.update(rw);
	}
}
void PanelManager::refreshAllPanelsTexture(){
	for(auto &mv: mpanels){
		mv.second.refreshAllButtonsTexture();
		mv.second.refreshTexture();
		mv.second.getSpecialButton().refreshTexture();
	}
}
