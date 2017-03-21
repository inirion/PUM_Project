#ifndef TEXTUREABLE_HPP_
#define TEXTUREABLE_HPP_

#include <string>
#include "Textures.hpp"

class Textureable{
protected:
	std::string texName;
	sf::Texture* texture;
public:
	Textureable(std::string tn=S::tex_unknown):
		texName(tn),
		texture(&Textures::get(texName))
	{}
	virtual ~Textureable(){}
	virtual inline void setTexture(std::string texId){texName=texId; texture=&Textures::get(texId);}// metoda ustawiająca teksturę na podaną w parametrze oraz przypisanie jej do wskaźnika klasy Texture.
	virtual inline std::string getTextureId(){return texName;}//metoda służąca do pobrania ID ustawionej tekstury.
	virtual inline void refreshTexture(){setTexture(texName);}// metoda odświeżająca teksturę w przypadku gdy tekstura została podmieniona.
};
#endif /* TEXTUREABLE_HPP_ */
