//============================================================================
// Name        : solution.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include "../include/solution.h"

solution::solution( instance& _cars ) { 
	cars = _cars;
	route = vector< unsigned >(cars.get_n());
	cost = numeric_limits< double >::max();
}

solution::~solution() { }

void solution::set_instance( instance& _cars ) { cars = _cars; }

void solution::set_route( const vector< unsigned >& _route ) { route = _route; }

void solution::set_vehicles( const vector< t_vec >& _vehicles ) { vehicles = _vehicles; }

void solution::set_cost( double _cost ) { cost = _cost; }

instance& solution::get_instance() { return cars; }

const vector< unsigned >& solution::get_route() const { return route; }

const vector< t_vec >& solution::get_vehicles() const { return vehicles; }

double solution::get_cost() { return cost; }

void solution::show_data() {
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = vehicles[k].begin; i < vehicles[k].end; i++)
			printf("%4d", vehicles[k].number);
	printf("\n");
	for(unsigned i = 0; i < cars.get_n(); i++)
		printf("%4d", route[i]);
	printf("\n");
}