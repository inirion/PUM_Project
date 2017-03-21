#ifndef COMMANDER_HPP_
#define COMMANDER_HPP_

#include <string>

class Commander{
private:
	std::string str;
	std::string next;

public:
	inline void clear(){// zapisanie wartości next w obiekcie str oraz usunięcie zawartości obiektu next.
		str=next;
		next.clear();
	}
	inline void operator<<(std::string in){// metoda przeciążająca operator <<.
		if(str.find(in)==str.npos){
			str+=" "+in;
		}
	}
	inline void toNext(std::string in){// metoda dodająca do końca obiektu next wartość podana w parametrze
		if(next.find(in)==next.npos){
			next+=" "+in;
		}
	}
	inline bool operator==(std::string in){// przeciążenie operatora porównania ==.
		return (str.find(in)!=str.npos);
	}

	inline const char* operator()(){//przeciążenie () powodującego zwrócenie danego stringa w postaci const char*.
		return str.c_str();
	}

};


#endif /* COMMANDER_HPP_ */
