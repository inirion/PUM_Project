#ifndef OBSERVABLE_HPP_
#define OBSERVABLE_HPP_

#include <vector>
#include <string>
#include "Listener.hpp"

class Observable{
protected:
	std::vector<Listener*> observers;
	ListenerMessage lmsg;

public:
	Observable(std::string cn, std::string on, std::string pn=""):
		lmsg(cn,on,pn)
	{}


	inline void setParent(std::string parent){lmsg.parentname=parent;}// ustawienie rodzica w klasie obserwatora.
	inline std::string getParent(){return lmsg.parentname;}// pobranie rodzica w klasie obserwatora.
	inline void setName(std::string name){lmsg.objectname=name;}// ustawienie nazwy obiektu obserwowanego.
	inline std::string getName(){return lmsg.objectname;}// pobranie obiektu obserwowanego.

	inline void addListener(Listener *ptr){//dodanie nowego obserwatora do wektora observers.
		for(const auto &p: observers){
			if(p == ptr) return;
		}
		observers.push_back(ptr);
	}
	inline void removeListener(Listener *ptr){// usunięcie wybranego obserwatora z wektora observers.
		for(size_t i=0; i<observers.size(); ++i){
			if(observers[i] == ptr) {
				observers.erase(observers.begin()+i);
				return;
			}
		}
	}

	inline void sendMessage(std::string arg, std::string val){//wysłanie wiadomości do wszystkich obserwatorów.
		lmsg.changes.clear();
		lmsg.changes[arg]=val;
		notifyListeners();
	}

	inline void notifyListeners(){//powiadomienie wszystkich obserwatorów wcześniej zainicjalizowaną wiadomością.
		for(auto &p: observers){
			p->notify(lmsg);
		}
	}

};


#endif /* OBSERVABLE_HPP_ */
