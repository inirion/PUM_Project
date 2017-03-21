#include "Sounds.hpp"
#include "S.hpp"

std::map<std::string,sf::SoundBuffer> Sounds::map;
bool Sounds::inited=false;

void Sounds::init(){
	if(!inited){
		inited=true;

		map[S::snd_null];
		map[S::snd_nullm];
		map[S::snd_error].loadFromFile("sound/err.ogg");
		map[S::snd_s1].loadFromFile("sound/s1.ogg");
		map[S::snd_s2].loadFromFile("sound/s2.ogg");
		map[S::snd_s3].loadFromFile("sound/s3.ogg");
		map[S::snd_fastshot1].loadFromFile("sound/fastshot1.ogg");
		map[S::snd_fastshot1m].loadFromFile("sound/fastshot1mono.ogg");
		map[S::snd_fastshot2].loadFromFile("sound/fastshot2.ogg");
		map[S::snd_fastshot2m].loadFromFile("sound/fastshot2mono.ogg");
		map[S::snd_fastshot3].loadFromFile("sound/fastshot3.ogg");
		map[S::snd_fastshot3m].loadFromFile("sound/fastshot3mono.ogg");
		map[S::snd_fastshot4].loadFromFile("sound/fastshot4.ogg");
		map[S::snd_fastshot4m].loadFromFile("sound/fastshot4mono.ogg");
		map[S::snd_fastshot5].loadFromFile("sound/fastshot5.ogg");
		map[S::snd_fastshot5m].loadFromFile("sound/fastshot5mono.ogg");
		map[S::snd_fastshot6].loadFromFile("sound/fastshot6.ogg");
		map[S::snd_fastshot6m].loadFromFile("sound/fastshot6mono.ogg");
		map[S::snd_cannon1].loadFromFile("sound/cannon1.ogg");
		map[S::snd_cannon1m].loadFromFile("sound/cannon1mono.ogg");
		map[S::snd_cannon2].loadFromFile("sound/cannon2.ogg");
		map[S::snd_cannon2m].loadFromFile("sound/cannon2mono.ogg");
		map[S::snd_cannon3].loadFromFile("sound/cannon3.ogg");
		map[S::snd_cannon3m].loadFromFile("sound/cannon3mono.ogg");
		map[S::snd_cannon4].loadFromFile("sound/cannon4.ogg");
		map[S::snd_cannon4m].loadFromFile("sound/cannon4mono.ogg");
		map[S::snd_electric1].loadFromFile("sound/electric1.ogg");
		map[S::snd_electric1m].loadFromFile("sound/electric1mono.ogg");
		map[S::snd_electric2].loadFromFile("sound/electric2.ogg");
		map[S::snd_electric2m].loadFromFile("sound/electric2mono.ogg");
		map[S::snd_electric3].loadFromFile("sound/electric3.ogg");
		map[S::snd_electric3m].loadFromFile("sound/electric3mono.ogg");
		map[S::snd_electric4].loadFromFile("sound/electric4.ogg");
		map[S::snd_electric4m].loadFromFile("sound/electric4mono.ogg");
	}
}

sf::SoundBuffer& Sounds::get(std::string id){
	if(map.find(id)!=map.end()){
		return map.at(id);
	}else{
		return map["error"];
	}
}
