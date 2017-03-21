/*
 * log.hpp
 *
 *  Created on: 13 kwi 2016
 *      Author: Piotr Okoń
 */
#ifndef LOG_HPP_
#define LOG_HPP_


#ifndef NONANDROID
	#include <android/log.h>

	#define LOG_TAG    "EARTHDEF-LOG"
	#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
	#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
	#define LOGF(...)  //__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Call function: " __VA_ARGS__)

#else
	#define LOGD(...) std::printf(__VA_ARGS__); std::printf("\n")
	#define LOGE(...) std::printf("ERROR: " __VA_ARGS__); std::printf("\n")
	#define LOGF(...) //std::printf("Call function: " __VA_ARGS__); std::printf("\n")
#endif


#endif /* LOG_HPP_ */
