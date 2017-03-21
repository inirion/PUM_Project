#include <string>

#ifndef TEXTABLE_HPP
#define TEXTABLE_HPP

class Textable{
protected:
	std::string text;
	sf::Vector2f textShift;

	int textSize;
	bool textCenter;
	bool textParse;
	float textOutlineSize;
	sf::Color textColor;
	sf::Color textOutlineColor;

public:
	Textable(std::string t="", int size=24):
		text(t),
		textSize(size),
		textCenter(true),
		textParse(true),
		textOutlineSize(0.0),
		textColor(sf::Color::White),
		textOutlineColor(sf::Color::Black)
	{}
	virtual ~Textable(){}

	inline const std::string& getText(){return text;}// metoda zwracająca wcześniej przypisany tekst.
	virtual inline void setText(std::string t){text=t;}//metoda przypisująca tekst.
	virtual inline void setTextShift(sf::Vector2f ts){textShift=ts;}//metoda przypisująca przesunięcie tekstu.
	virtual inline void setTextSize(int size){textSize=size;}//metoda zmieniająca wielkość czcionki tekstu.
	virtual inline void setTextCenter(bool val){textCenter=val;}//metoda boolowska ustawiająca czy dany jest jest wyśrodkowany.
	virtual inline void setTextParse(bool val){textParse=val;}//metoda boolowska ustawiająca czy dany jest jest sparsowany.
	virtual inline bool getTextParse()const{return textParse;}//metoda boolowska informująca o tym czy dany jest był sparsowany.
	virtual inline void setTextColor(sf::Color c){textColor=c;}// metoda zmieniająca kolor tekstu.
	virtual inline void setTextOutlineColor(sf::Color c){textOutlineColor=c;}
	virtual inline void setTextOutlineSize(float v){textOutlineSize=v;}
};

#endif
