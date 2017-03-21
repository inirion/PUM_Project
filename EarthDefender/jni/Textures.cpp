#include "Textures.hpp"
#include "S.hpp"
#include "log.hpp"
#include <exception>

std::map<std::string,sf::Texture> Textures::map;
bool Textures::inited=false;

void Textures::init(bool force){
	if(!inited || force){		
		std::string p;
		
		if(Conf::textureDivisor==2){
			p=S::prefix_half;
		}
		
		std::string d="img/";

		map.clear();
		try{
			map[S::tex_null];
			map[S::tex_unknown].loadFromFile(d+p+"unknown.png");
			map[S::tex_unknown].setSmooth(true);
			map[S::tex_background].loadFromFile(d+p+"background.png");
			map[S::tex_background].setSmooth(true);
			map[S::tex_button].loadFromFile(d+p+"button.png");
			map[S::tex_button].setSmooth(true);
			map[S::tex_checked].loadFromFile(d+p+"checked.png");
			map[S::tex_checked].setSmooth(true);
			map[S::tex_unchecked].loadFromFile(d+p+"unchecked.png");
			map[S::tex_unchecked].setSmooth(true);
			map[S::tex_squarebutton].loadFromFile(d+p+"squarebutton.png");
			map[S::tex_squarebutton].setSmooth(true);
			map[S::tex_sell].loadFromFile(d+p+"sell.png");
			map[S::tex_sell].setSmooth(true);
			map[S::tex_bar].loadFromFile(d+p+"bar.png");
			map[S::tex_bar].setSmooth(true);
			map[S::tex_upgrade].loadFromFile(d+p+"upgrade.png");
			map[S::tex_upgrade].setSmooth(true);

			map[S::tex_tower_gatling_1].loadFromFile(d+"tower/gatling/"+p+"v1.png");
			map[S::tex_tower_gatling_1].setSmooth(true);
			map[S::tex_tower_gatling_2].loadFromFile(d+"tower/gatling/"+p+"v2.png");
			map[S::tex_tower_gatling_2].setSmooth(true);
			map[S::tex_tower_gatling_3].loadFromFile(d+"tower/gatling/"+p+"v3.png");
			map[S::tex_tower_gatling_3].setSmooth(true);

			map[S::tex_tower_lightcannon_1].loadFromFile(d+"tower/lightcannon/"+p+"v1.png");
			map[S::tex_tower_lightcannon_1].setSmooth(true);
			map[S::tex_tower_lightcannon_2].loadFromFile(d+"tower/lightcannon/"+p+"v2.png");
			map[S::tex_tower_lightcannon_2].setSmooth(true);
			map[S::tex_tower_lightcannon_3].loadFromFile(d+"tower/lightcannon/"+p+"v3.png");
			map[S::tex_tower_lightcannon_3].setSmooth(true);

			map[S::tex_tower_coil_1].loadFromFile(d+"tower/coil/"+p+"v1.png");
			map[S::tex_tower_coil_1].setSmooth(true);
			map[S::tex_tower_coil_2].loadFromFile(d+"tower/coil/"+p+"v2.png");
			map[S::tex_tower_coil_2].setSmooth(true);
			map[S::tex_tower_coil_3].loadFromFile(d+"tower/coil/"+p+"v3.png");
			map[S::tex_tower_coil_3].setSmooth(true);

			map[S::tex_tower_rocketlauncher_1].loadFromFile(d+"tower/rocketlauncher/"+p+"v1.png");
			map[S::tex_tower_rocketlauncher_1].setSmooth(true);
			map[S::tex_tower_rocketlauncher_2].loadFromFile(d+"tower/rocketlauncher/"+p+"v2.png");
			map[S::tex_tower_rocketlauncher_2].setSmooth(true);
			map[S::tex_tower_rocketlauncher_3].loadFromFile(d+"tower/rocketlauncher/"+p+"v3.png");
			map[S::tex_tower_rocketlauncher_3].setSmooth(true);

			map[S::tex_color_black].loadFromFile(d+"color/black.png");
			map[S::tex_color_white].loadFromFile(d+"color/white.png");
			map[S::tex_color_dgray].loadFromFile(d+"color/dgray.png");
			map[S::tex_color_lgray].loadFromFile(d+"color/lgray.png");
			map[S::tex_color_red].loadFromFile(d+"color/red.png");
			map[S::tex_color_green].loadFromFile(d+"color/green.png");
			map[S::tex_color_blue].loadFromFile(d+"color/blue.png");
			map[S::tex_color_cyan].loadFromFile(d+"color/cyan.png");
			map[S::tex_color_magenta].loadFromFile(d+"color/magenta.png");
			map[S::tex_color_yellow].loadFromFile(d+"color/yellow.png");

			map[S::tex_map_asphalt].loadFromFile(d+"map/"+p+"asphalt.png");
			map[S::tex_map_asphalt].setSmooth(true);

			map[S::tex_map_grass].loadFromFile(d+"map/"+p+"grass.png");
			map[S::tex_map_grass].setSmooth(true);
			map[S::tex_map_grassanim].loadFromFile(d+"map/"+p+"grassanim.png");
			map[S::tex_map_grassanim].setSmooth(true);
			map[S::tex_map_debugtile].loadFromFile(d+"map/"+p+"debugtile.png");
			map[S::tex_map_debugtile].setSmooth(true);
			map[S::tex_map_selectedtile].loadFromFile(d+"map/"+p+"selectedtile.png");
			map[S::tex_map_selectedtile].setSmooth(true);
			map[S::tex_map_base].loadFromFile(d+"map/"+p+"base.png");
			map[S::tex_map_base].setSmooth(true);

			map[S::tex_enemy_lighthovercraft].loadFromFile(d+"enemy/"+p+"lighthovercraft.png");
			map[S::tex_enemy_lighthovercraft].setSmooth(true);
			map[S::tex_enemy_lightbomber].loadFromFile(d+"enemy/"+p+"lightbomber.png");
			map[S::tex_enemy_lightbomber].setSmooth(true);

			map[S::tex_brush_soft].loadFromFile(d+"brush/soft.png");
			map[S::tex_brush_soft].setSmooth(true);
			map[S::tex_brush_medium].loadFromFile(d+"brush/medium.png");
			map[S::tex_brush_medium].setSmooth(true);
			map[S::tex_brush_hard].loadFromFile(d+"brush/hard.png");
			map[S::tex_brush_hard].setSmooth(true);

			map[S::tex_blend].loadFromFile(d+p+"blend.png");
			map[S::tex_blend].setSmooth(true);

			map[S::tex_fx_explode].loadFromFile(d+"fx/"+p+"explode.png");
			map[S::tex_fx_explode].setSmooth(true);
			map[S::tex_fx_muzzleflash].loadFromFile(d+"fx/"+p+"muzzleflash.png");
			map[S::tex_fx_muzzleflash].setSmooth(true);
			map[S::tex_fx_lightning].loadFromFile(d+"fx/"+p+"lightning.png");
			map[S::tex_fx_lightning].setSmooth(true);

			map[S::tex_rocket].loadFromFile(d+p+"rocket.png");
			map[S::tex_rocket].setSmooth(true);
			
			inited=true;			
		}catch(std::exception &e){
			if(Conf::textureDivisor==1){
				
				Conf::textureDivisor*=2;
				init();
			}
		}
	}
}

sf::Texture& Textures::get(std::string id){
	if(map.find(id)!=map.end()){
		return map.at(id);
	}else{
		return map["unknown"];
	}
}
