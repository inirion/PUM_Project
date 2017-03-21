#ifndef LANG_HPP_
#define LANG_HPP_

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "log.hpp"
#include "S.hpp"

sf::String s2ws(std::string str);//Zamiana std::string na sf::String UTF32
std::string ws2s(sf::String str);//Zamiana sf::String UTF32 na std::string

class Lang{
private:
	static bool inited;

	static size_t deflang;
	static size_t selected;

	static std::vector<std::string> languages;
	static std::map<std::string, std::string> m;
public:

	static void init();// metoda inicjalizująca wektor języków dostępnych w grze.
	static sf::String translate(std::string in);//uzyskanie tłumaczenia w postaci sf::String UTF32.
	static std::string translateRaw(std::string in);//uzyskanie tłumaczenia w postaci std::string.

	static inline const std::vector<std::string>& getLanguages(){return languages;}// metoda zwracająca referencję wektora języków.
	static inline const std::string& getSelected(){return languages[selected];}// metoda zwracająca referencję na wybrany język.
	static inline const void set2Next(){++selected; if(selected==languages.size()){selected=0;} } // metoda zmieniająca język na następny, zmiana to dokonuje się po przyciśnięciu zmiany języka w opcjach gry.
	static inline const void set2Prev(){--selected; if(selected==0){selected=languages.size()-1;} }// metoda zmieniająca język na poprzedni, zmiana to dokonuje się po przyciśnięciu zmiany języka w opcjach gry.
};

#define l(IN) Lang::translate(IN)
#define ll(IN) Lang::translateRaw(IN)


std::string lineScroll(std::string str,const unsigned int first=0, const unsigned int last=0);	//Funkcja zwracająca tekst od danej lini do danej lini
void formatText(sf::Text &text, sf::FloatRect rect);


#endif /* LANG_HPP_ */

