#ifndef LISTENER_HPP_
#define LISTENER_HPP_

#include "ListenerMessage.hpp"

class Listener{
public:
	virtual ~Listener(){};
	virtual void notify(ListenerMessage &msg)=0;
};

#endif /* LISTENER_HPP_ */
