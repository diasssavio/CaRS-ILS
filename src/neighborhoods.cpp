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

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();

	solution current = p_sol;

	// Evaluating all possible swaps
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned j = i + 1; j < v_pos[k].second; j++) {
				vector< unsigned > route(p_sol.get_route());

				// Aux variable to calculate the last edge of the cicle
				unsigned aux = j + 1;
				if(j == (n - 1)) aux = 0;

				// Calculating the current cost for the swap change
				double cost = p_sol.get_cost();
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
					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(p_sol.get_vehicles());
					neighbor.set_pos(p_sol.get_pos());
					neighbor.set_cost(cost);
					current = neighbor;
				}
				// cout << "... executed!" << endl;
			}

	return current;
}

solution neighborhoods::swap_two( solution& p_sol ) {
	// TODO
}

solution neighborhoods::swap_three( solution& p_sol ) {
	// TODO
}

solution neighborhoods::two_opt( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();

	solution current = p_sol;

	// Evaluating all possible swaps
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned j = i + 3; j < v_pos[k].second; j++) {
				vector< unsigned > route(p_sol.get_route());

				// Aux variable to calculate the last edge of the cicle
				unsigned aux = j + 1;
				if(j == (n - 1)) aux = 0;

				// Calculating the current cost for the 2-opt change
				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[j] ][ route[aux] ];
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
				cost += distances[ vehicles[k].number ][ route[i] ][ route[aux] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					reverse(route.begin() + i, route.begin() + (j + 1));
					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(p_sol.get_vehicles());
					neighbor.set_pos(p_sol.get_pos());
					neighbor.set_cost(cost);
					current = neighbor;
				}
			}

	return current;
}

solution neighborhoods::shift_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();

	solution current = p_sol;

	// Evaluating all possible swaps
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second; i++)
			for(unsigned j = v_pos[k].first + 1; j < v_pos[k].second; j++) {
				// If i == j + 1 means that I'll try to insert i in its same position as before
				if(i == j || i == (j + 1)) continue;

				vector< unsigned > route(p_sol.get_route());

				// Aux variable to calculate the last edge of the cicle
				unsigned aux1 = i + 1;
				if(i == (n - 1)) aux1 = 0;
				unsigned aux2 = j + 1;
				if(j == (n - 1)) aux2 = 0;

				// Calculating the current cost for the or-opt-1 change
				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[i] ][ route[aux1] ];
				cost -= distances[ vehicles[k].number ][ route[j] ][ route[aux2] ];
				cost += distances[ vehicles[k].number ][ route[j] ][ route[i] ];
				cost += distances[ vehicles[k].number ][ route[i] ][ route[aux2] ];
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[aux1] ];
				// if(i == (j - 1))
					// cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					unsigned value = route[i];
					if(i > j) {
						route.erase(route.begin() + i);
						route.insert(route.begin() + (j + 1), value);
					} else {
						route.insert(route.begin() + (j + 1), value);
						route.erase(route.begin() + i);
					}
					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(p_sol.get_vehicles());
					neighbor.set_pos(p_sol.get_pos());
					neighbor.set_cost(cost);
					current = neighbor;
				}
			}

	return current;
}

solution neighborhoods::shift_two( solution& p_sol ) {
	// TODO
}

solution neighborhoods::shift_three( solution& p_sol ) {
	// TODO
}

solution& neighborhoods::execute( solution& p_sol ) {
	bool is_improved = true;
	best = p_sol;
	solution current = p_sol;
	while(is_improved) {
		// current = swap_one(current);
		// current = two_opt(current);
		current = shift_one(current);
		if(current.get_cost() < best.get_cost())
			best = current;
		else is_improved = false;
	}

	return best;
}