//============================================================================
// Name        : logger.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include "../include/logger.h"

logger::logger() { }

logger::logger( FWChrono& _timer ) { this->timer = _timer; }

logger::~logger() { }

void logger::make_log( double cost ) {
	it_log.push_back(make_pair(cost, ++iteration));
	times.push_back(((double) timer.getMilliSpan() / 1000));
}