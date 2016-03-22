//============================================================================
// Name        : neighborhoods.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#ifndef NEIGHBORHOODS_H_
#define NEIGHBORHOODS_H_

#include "instance.h"
#include "solution.h"
#include "constructor.h"
#include "mt19937ar.h"

#include <utility>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

class neighborhoods {
private:	
	// Input instance
	instance cars;

	// Result best solution
	solution best;

public:
	neighborhoods( instance& );
	virtual ~neighborhoods();

	// TSP (route) Neighborhoods
	// Swap-exchange neighborhoods
	solution swap_one( solution& );
	solution swap_two( solution& );
	solution swap_three( solution& );

	// K-opt neighborhoods
	solution two_opt( solution& );

	// Or-Opt (Shift) neighborhoods
	solution shift_one( solution& );
	solution shift_two( solution& );
	solution shift_three( solution& );

	// Vehicles neighborhoods
	solution exchange( solution& );
	solution extend_contract( solution& );

	solution& execute( solution& );
	
};

#endif /* NEIGHBORHOODS_H_ */