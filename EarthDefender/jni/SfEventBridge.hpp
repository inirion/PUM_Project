/*
 * sfEventBridge.hpp
 *
 *  Created on: 2016-04-29
 *      Author: jakub
 */

#ifndef SFEVENTBRIDGE_HPP_
#define SFEVENTBRIDGE_HPP_

#include "Observable.hpp"

class SfEventBridge : public Observable{
public:
	SfEventBridge():
		Observable(S::class_sfeventbridge,"bridge")
		{}
};


#endif /* SFEVENTBRIDGE_HPP_ */
