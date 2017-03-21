#ifndef LISTENERMESSAGE_HPP
#define LISTENERMESSAGE_HPP

#include <map>
#include <string>

class ListenerMessage{
public:
	std::string classname;
	std::string objectname;
	std::string parentname;
	void* sender;
	std::map<std::string, std::string> changes;

	ListenerMessage(std::string cn, std::string on, std::string pn=""):
		classname(cn),
		objectname(on),
		parentname(pn),
		sender(this)
	{}

	inline ListenerMessage operator=(ListenerMessage &o){//metoda przeciążająca operator przypisania oraz zwracająca referencję na obiekt.
		objectname=o.objectname;
		parentname=o.parentname;
		return *this;
	}
	inline ListenerMessage operator=(ListenerMessage o){//metoda przeciążająca operator przypisania oraz zwracająca referencję na obiekt.
		objectname=o.objectname;
		parentname=o.parentname;
		return *this;
	}
};

#endif
