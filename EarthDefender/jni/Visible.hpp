#ifndef VISABLE_HPP_
#define VISABLE_HPP_

class Visible{
protected:
	bool visible;

public:
	Visible(): visible(true){}

	inline bool isVisible(){return visible;}// metoda informująca o tym czy obiekt jest widoczny.
	inline void setVisible(bool val){ visible=val; }//metoda ustawiająca widoczność obiektu.
};



#endif /* VISABLE_HPP_ */
