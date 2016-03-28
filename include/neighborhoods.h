//============================================================================
// Name        : neighborhoods.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Neighborhoods class interface
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

	// TSP (route) Neighborhoods -- INNER ROUTES
	// Swap-exchange neighborhoods
	solution i_swap_one( solution& );
	solution i_swap_two( solution& );
	solution i_swap_three( solution& );

	// K-opt neighborhoods
	solution i_two_opt( solution& );

	// Or-Opt (Shift) neighborhoods
	solution i_shift_one( solution& );
	solution i_shift_two( solution& );
	solution i_shift_three( solution& );

	// TSP (route) Neighborhoods -- OUTTER ROUTES
	// Swap-exchange neighborhoods
	solution o_swap_one( solution& );
	solution o_swap_two( solution& );
	solution o_swap_three( solution& );

	// Or-Opt (Shift) neighborhoods
	solution o_shift_one( solution& );
	solution o_shift_two( solution& );
	solution o_shift_three( solution& );

	// Vehicles neighborhoods
	solution exchange( solution& );
	solution extend_contract( solution& );
	solution extend_contract_one( solution& );

	solution& execute( solution& );
	
};

#endif /* NEIGHBORHOODS_H_ */