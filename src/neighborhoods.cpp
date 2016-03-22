//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include "../include/neighborhoods.h"

neighborhoods::neighborhoods( instance& _cars ) { this->cars = _cars; }

neighborhoods::~neighborhoods() { }

solution neighborhoods::swap_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< unsigned > route = p_sol.get_route();
	vector< t_vec > vehicles = p_sol.get_vehicles();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();

	for(unsigned k = 0; k < vehicles.size(); k++) {
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second; i++) {
			if(vehicles[k].end == route[i + 1]) {
				k++;
				break;
			}
		}
	}
}