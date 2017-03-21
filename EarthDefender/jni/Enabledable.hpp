#ifndef ENABLEDABLE_HPP_
#define ENABLEDABLE_HPP_

class Enabledable{
protected:
	bool enabled;

public:
	Enabledable():
		enabled(true)
	{}

	inline bool isEnabled(){return enabled;}// metoda boolowka zwracająca pole enabled tej klasy.
	inline void setEnabled(bool val){enabled=val;}// setter boolowski ustawiający enabled na dany stan.
};


#endif /* ENABLEDABLE_HPP_ */
