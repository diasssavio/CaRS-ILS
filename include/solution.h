//============================================================================
// Name        : solution.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>

#include "instance.h"

using namespace std;

typedef struct vehicle{
	unsigned number;
	unsigned begin, end;
} t_vec;

class solution {
private:
	// Instance data class
	instance cars;

	// Solution itself
	vector< unsigned > route;
	vector< t_vec > vehicles;

	// Solution cost
	double cost;

public:
	// Constructors & destructor
	solution( instance& );
	virtual ~solution();

	// Setters
	void set_instance( instance& );
	void set_route( const vector< unsigned >& );
	void set_vehicles( const vector< t_vec >& );
	void set_cost( double );

	// Getters
	instance& get_instance();
	const vector< unsigned >& get_route() const;
	const vector< t_vec >& get_vehicles() const;
	double get_cost();

	// Useful Methods
	void show_data();

};

#endif /* SOLUTION_H_ */