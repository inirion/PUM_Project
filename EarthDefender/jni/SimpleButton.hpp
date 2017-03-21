#ifndef SIMPLEBUTTON_HPP_
#define SIMPLEBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hoverable.hpp"
#include "Textures.hpp"
#include "Enabledable.hpp"
#include "Visible.hpp"
#include "Textable.hpp"
#include "Textureable.hpp"
#include "Sounds.hpp"
#include "PosReferenceable.hpp"
#include "Observable.hpp"

class SimpleButton:
	public Observable,
	public Textable,
	public Textureable,
	public Hoverable,
	public sf::Drawable,
	public Enabledable,
	public Visible,
	public PosReferenceable
	{
protected:
	bool clicked;

	sf::Sound clickSound;
	std::string imageTexName;
	sf::Texture *imageTex;
	sf::IntRect imageTexRectAbsolute;
	sf::IntRect imageTexRect;
	float imageScale;

public:
	SimpleButton(std::string s="", int size = 18, std::string parent=""):
		Observable(S::class_simplebutton,s,parent),
		Textable(s,size),
		Textureable(S::tex_button),
		clicked(false),
		imageTex(NULL),
		imageScale(1.0f)
	{
		textOutlineSize=2.0;
	}
	void update(sf::RenderWindow &rw);// metoda odświeżająca dany obiekt.
	void setImageTextureRect(sf::IntRect ir);//metoda ustawiająca Rectangle danej tekstury.

	inline void setSound(std::string soundId){clickSound.setBuffer(Sounds::get(soundId));}//metoda ustawiająca głos dla przycisku podczas kliknięcia.
	inline void setImageTexture(std::string texId){ imageTexName=texId; if(imageTexName.empty()){imageTex=NULL;} else imageTex=&Textures::get(imageTexName);}//metoda ustawiająca teksturę danego przycisku.
	inline void refreshImageTexture(){setImageTexture(imageTexName); setImageTextureRect(imageTexRectAbsolute);}
	inline void setImageScale(float v){imageScale=v;}
	inline bool isClicked(){return clicked;}// metoda zwracająca informacje o tym czy przycisk został kliknięty czy nie.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
};

#endif
