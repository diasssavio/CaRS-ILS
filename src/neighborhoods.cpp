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
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();
	vector< matrix_2d > return_rates = cars.get_return_rates();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();

	solution current = p_sol;

	// Evaluating all possible swaps
	for(unsigned k = 0; k < vehicles.size(); k++) {
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++) {
			for(unsigned j = i + 1; j < v_pos[k].second; j++) {
				solution neighbor(p_sol);
				vector< unsigned > route = neighbor.get_route();

				// Aux variable to calculate the last edge of the cicle
				unsigned aux = j + 1;
				if(j == (n - 1)) aux = 0;

				// Calculating the current cost for the swap change
				double cost = neighbor.get_cost();
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
				cost += distances[ vehicles[k].number ][ route[i] ][ route[aux] ];
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[j] ][ route[aux] ];
				cost -= distances[ vehicles[k].number ][ route[i] ][ route[i + 1] ];
				
				// If i & j are adjacent
				if(j == i + 1)
					cost += distances[ vehicles[k].number ][ route[j] ][ route[i] ];
				else { // otherwise
					cost += distances[ vehicles[k].number ][ route[j] ][ route[i + 1] ];
					cost += distances[ vehicles[k].number ][ route[j - 1] ][ route[i] ];
					cost -= distances[ vehicles[k].number ][ route[j - 1] ][ route[j] ];
				}
				

				// If the cost is smaller than the current, the change is applied
				// cout << cost << " - " << neighbor.evaluate() << " = " << cost - neighbor.evaluate() << endl;
				if(cost < current.get_cost()) {
					swap(route[i], route[j]);
					neighbor.set_cost(cost);
					neighbor.set_route(route);
					current = neighbor;
				}
				// cout << "... executed!" << endl;
			}
		}
	}

	return current;
}

solution& neighborhoods::execute( solution& p_sol ) {
	bool is_improved = true;
	best = p_sol;
	solution current = p_sol;
	while(is_improved) {
		current = swap_one(current);
		if(current.get_cost() < best.get_cost())
			best = current;
		else is_improved = false;
	}

	return best;
}