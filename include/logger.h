//============================================================================
// Name        : logger.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#ifndef LOGGER_H_
#define LOGGER_H_

#include "FWChrono.h"

#include <utility>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

class logger {
private:
	// Parameters
	unsigned iteration = 0;

	// Logs
	vector< pair< double, unsigned > > it_log;
	vector< double > times;
	FWChrono timer;

public:
	logger();
	logger( FWChrono& );
	virtual ~logger();

	void make_log( double );
	
};

#endif /* LOGGER_H_ */