//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Neighborhoods class implementation
//============================================================================

#include "../include/neighborhoods.h"

neighborhoods::neighborhoods( instance& _cars ) { this->cars = _cars; }

neighborhoods::~neighborhoods() { }

solution neighborhoods::i_swap_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned j = i + 1; j < v_pos[k].second; j++) {
				// Aux variable to calculate the last edge of the cycle
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
				if(cost < current_cost) {
					i_swap = i;
					j_swap = j;
					current_cost = cost;
				}
				// cout << "... executed!" << endl;
			}

	if(i_swap != j_swap) {
		swap(route[i_swap], route[j_swap]);
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::i_swap_two( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 2; i++)
			for(unsigned j = i + 2; j < v_pos[k].second - 1; j++) {
				// Aux variable to calculate the last edge of the cycle
				unsigned aux = j + 2;
				if(j == (n - 2)) aux = 0;

				// Calculating the current cost for the swap change
				double cost = p_sol.get_cost();
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
				cost += distances[ vehicles[k].number ][ route[i + 1] ][ route[aux] ];
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[j + 1] ][ route[aux] ];
				cost -= distances[ vehicles[k].number ][ route[i + 1] ][ route[i + 2] ];
				
				// If i & j are adjacent
				if(j == i + 2)
					cost += distances[ vehicles[k].number ][ route[j + 1] ][ route[i] ];
				else { // otherwise
					cost += distances[ vehicles[k].number ][ route[j + 1] ][ route[i + 2] ];
					cost += distances[ vehicles[k].number ][ route[j - 1] ][ route[i] ];
					cost -= distances[ vehicles[k].number ][ route[j - 1] ][ route[j] ];
				}
				
				// If the cost is smaller than the current, the change is applied
				// cout << cost << " - " << neighbor.evaluate() << " = " << cost - neighbor.evaluate() << endl;
				if(cost < current_cost) {
					i_swap = i;
					j_swap = j;
					current_cost = cost;
				}
				// cout << "... executed!" << endl;
			}

	if(i_swap != j_swap) {
		// cout << "Applying swap_2" << endl;
		swap(route[i_swap], route[j_swap]);
		swap(route[i_swap + 1], route[j_swap + 1]);
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::i_swap_three( solution& p_sol ) {
	// TODO
}

solution neighborhoods::i_two_opt( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible swaps
	unsigned i_opt = 0, j_opt = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned j = i + 3; j < v_pos[k].second; j++) {
				// Aux variable to calculate the last edge of the cycle
				unsigned aux = j + 1;
				if(j == (n - 1)) aux = 0;

				// Calculating the current cost for the 2-opt change
				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[j] ][ route[aux] ];
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
				cost += distances[ vehicles[k].number ][ route[i] ][ route[aux] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current_cost) {
					i_opt = i;
					j_opt = j + 1;
					current_cost = cost;
				}
			}

	if(i_opt != j_opt) {
		reverse(route.begin() + i_opt, route.begin() + j_opt);
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::i_shift_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible shifts
	unsigned i_shift = 0, j_shift = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second; i++)
			for(unsigned j = v_pos[k].first; j < v_pos[k].second; j++) {
				// If i == j + 1 means that I'll try to insert i in its same position as before
				if(i == j || i == (j + 1)) continue;

				// Aux variable to calculate the last edge of the cycle
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

				// If the cost is smaller than the current, the change is applied
				if(cost < current_cost) {
					i_shift = i;
					j_shift = j;
					current_cost = cost;
				}
			}

	if(i_shift != j_shift) {
		unsigned value = route[i_shift];
		if(i_shift > j_shift) {
			route.erase(route.begin() + i_shift);
			route.insert(route.begin() + (j_shift + 1), value);
		} else {
			route.insert(route.begin() + (j_shift + 1), value);
			route.erase(route.begin() + i_shift);
		}
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::i_shift_two( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible shifts
	unsigned i_shift = 0, j_shift = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned j = v_pos[k].first; j < v_pos[k].second; j++) {
				// If i == j + 1 means that I'll try to insert i in its same position as before
				if(i == j || i == (j + 1) || i == (j - 1)) continue;

				// Aux variable to calculate the last edge of the cycle
				unsigned aux1 = i + 2;
				if(i == (n - 2)) aux1 = 0;
				unsigned aux2 = j + 1;
				if(j == (n - 1)) aux2 = 0;

				// Calculating the current cost for the or-opt-1 change
				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
				cost -= distances[ vehicles[k].number ][ route[i + 1] ][ route[aux1] ];
				cost -= distances[ vehicles[k].number ][ route[j] ][ route[aux2] ];
				cost += distances[ vehicles[k].number ][ route[j] ][ route[i] ];
				cost += distances[ vehicles[k].number ][ route[i + 1] ][ route[aux2] ];
				cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[aux1] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current_cost) {
					i_shift = i;
					j_shift = j;
					current_cost = cost;
				}
			}

	if(i_shift != j_shift) {
		// cout << "Applying shift_2" << endl;
		unsigned value1 = route[i_shift], value2 = route[i_shift + 1];
		if(i_shift > j_shift) {
			route.erase(route.begin() + i_shift);
			route.erase(route.begin() + i_shift);
			route.insert(route.begin() + (j_shift + 1), value2);
			route.insert(route.begin() + (j_shift + 1), value1);
		} else {
			route.insert(route.begin() + (j_shift + 1), value2);
			route.insert(route.begin() + (j_shift + 1), value1);
			route.erase(route.begin() + i_shift);
			route.erase(route.begin() + i_shift);
		}
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::i_shift_three( solution& p_sol ) {
	// TODO
}

solution neighborhoods::o_swap_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size() - 1; k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second; i++)
			for(unsigned l = k + 1; l < vehicles.size(); l++)
				for(unsigned j = v_pos[l].first + 1; j < v_pos[l].second; j++) {
					// Aux variable to calculate the last edge of the cycle
					unsigned aux = j + 1;
					if(j == (n - 1)) aux = 0;

					// Calculating the current cost for the swap change
					double cost = p_sol.get_cost();
					cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
					cost += distances[ vehicles[l].number ][ route[j - 1] ][ route[i] ];
					cost += distances[ vehicles[k].number ][ route[j] ][ route[i + 1] ];
					cost += distances[ vehicles[l].number ][ route[i] ][ route[aux] ];
					cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
					cost -= distances[ vehicles[l].number ][ route[j - 1] ][ route[j] ];
					cost -= distances[ vehicles[k].number ][ route[i] ][ route[i + 1] ];
					cost -= distances[ vehicles[l].number ][ route[j] ][ route[aux] ];					

					// If the cost is smaller than the current, the change is applied
					// cout << cost << " - " << neighbor.evaluate() << " = " << cost - neighbor.evaluate() << endl;
					if(cost < current_cost) {
						i_swap = i;
						j_swap = j;
						current_cost = cost;
					}
					// cout << "... executed!" << endl;
				}

	if(i_swap != j_swap) {
		swap(route[i_swap], route[j_swap]);
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::o_swap_two( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();

	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size() - 1; k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned l = k + 1; l < vehicles.size(); l++)
				for(unsigned j = v_pos[l].first + 1; j < v_pos[l].second - 1; j++) {
					// Aux variable to calculate the last edge of the cycle
					unsigned aux = j + 2;
					if(j == (n - 2)) aux = 0;

					// Calculating the current cost for the swap change
					double cost = p_sol.get_cost();
					cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[j] ];
					cost += distances[ vehicles[l].number ][ route[j - 1] ][ route[i] ];
					cost += distances[ vehicles[k].number ][ route[j + 1] ][ route[i + 2] ];
					cost += distances[ vehicles[l].number ][ route[i + 1] ][ route[aux] ];
					cost += distances[ vehicles[l].number ][ route[i] ][ route[i + 1] ];
					cost += distances[ vehicles[k].number ][ route[j] ][ route[j + 1] ];
					cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
					cost -= distances[ vehicles[l].number ][ route[j - 1] ][ route[j] ];
					cost -= distances[ vehicles[k].number ][ route[i + 1] ][ route[i + 2] ];
					cost -= distances[ vehicles[l].number ][ route[j + 1] ][ route[aux] ];
					cost -= distances[ vehicles[k].number ][ route[i] ][ route[i + 1] ];
					cost -= distances[ vehicles[l].number ][ route[j] ][ route[j + 1] ];

					// If the cost is smaller than the current, the change is applied
					// cout << cost << " - " << neighbor.evaluate() << " = " << cost - neighbor.evaluate() << endl;
					if(cost < current_cost) {
						i_swap = i;
						j_swap = j;
						current_cost = cost;
					}
					// cout << "... executed!" << endl;
				}

	if(i_swap != j_swap) {
		cout << "Applying o_swap_2" << endl;
		swap(route[i_swap], route[j_swap]);
		swap(route[i_swap + 1], route[j_swap + 1]);
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::o_swap_three( solution& p_sol ) {
	// TODO
}

solution neighborhoods::o_shift_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< matrix_2d > distances = cars.get_distances();

	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible shifts
	unsigned i_shift = 0, j_shift = 0, k_shift = 0, l_shift = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second; i++)
			for(unsigned l = 0; l < vehicles.size(); l++) {
				if(k == l) continue;
				for(unsigned j = v_pos[l].first; j < v_pos[l].second; j++) {

					// Aux variable to calculate the last edge of the cycle
					unsigned aux1 = i + 1;
					if(i == (n - 1)) aux1 = 0;
					unsigned aux2 = j + 1;
					if(j == (n - 1)) aux2 = 0;

					// Calculating the current cost for the or-opt-1 change
					double cost = p_sol.get_cost();
					cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
					cost -= distances[ vehicles[k].number ][ route[i] ][ route[aux1] ];
					cost -= distances[ vehicles[l].number ][ route[j] ][ route[aux2] ];
					cost += distances[ vehicles[l].number ][ route[j] ][ route[i] ];
					cost += distances[ vehicles[l].number ][ route[i] ][ route[aux2] ];
					cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[aux1] ];

					// If the cost is smaller than the current, the change is applied
					if(cost < current_cost) {
						i_shift = i;
						j_shift = j;
						k_shift = k;
						l_shift = l;
						current_cost = cost;
					}
				}
			}

	if(k_shift != l_shift) {
		unsigned value = route[i_shift];
		if(k_shift > l_shift) {
			route.erase(route.begin() + i_shift);
			route.insert(route.begin() + (j_shift + 1), value);
			
			// Updating the position of the intermediate routes
			for(unsigned k = l_shift + 1; k < k_shift; k++) {
				v_pos[k].first++;
				v_pos[k].second++;
			}
			v_pos[k_shift].first++;
			v_pos[l_shift].second++;
		} else {
			route.insert(route.begin() + (j_shift + 1), value);
			route.erase(route.begin() + i_shift);

			// Updating the position of the intermediate routes
			for(unsigned k = k_shift + 1; k < l_shift; k++) {
				v_pos[k].first--;
				v_pos[k].second--;
			}
			v_pos[k_shift].second--;
			v_pos[l_shift].first--;
		}
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::o_shift_two( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< matrix_2d > distances = cars.get_distances();

	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
	vector< unsigned > route(p_sol.get_route());

	// Evaluating all possible shifts
	unsigned i_shift = 0, j_shift = 0, k_shift = 0, l_shift = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned k = 0; k < vehicles.size(); k++)
		for(unsigned i = v_pos[k].first + 1; i < v_pos[k].second - 1; i++)
			for(unsigned l = 0; l < vehicles.size(); l++) {
				if(k == l) continue;
				for(unsigned j = v_pos[l].first; j < v_pos[l].second; j++) {

					// Aux variable to calculate the last edge of the cycle
					unsigned aux1 = i + 2;
					if(i == (n - 2)) aux1 = 0;
					unsigned aux2 = j + 1;
					if(j == (n - 1)) aux2 = 0;

					// Calculating the current cost for the or-opt-1 change
					double cost = p_sol.get_cost();
					cost -= distances[ vehicles[k].number ][ route[i - 1] ][ route[i] ];
					cost -= distances[ vehicles[k].number ][ route[i] ][ route[i + 1] ];
					cost -= distances[ vehicles[k].number ][ route[i + 1] ][ route[aux1] ];
					cost -= distances[ vehicles[l].number ][ route[j] ][ route[aux2] ];
					cost += distances[ vehicles[l].number ][ route[j] ][ route[i] ];
					cost += distances[ vehicles[l].number ][ route[i] ][ route[i + 1] ];
					cost += distances[ vehicles[l].number ][ route[i + 1] ][ route[aux2] ];
					cost += distances[ vehicles[k].number ][ route[i - 1] ][ route[aux1] ];

					// If the cost is smaller than the current, the change is applied
					if(cost < current_cost) {
						i_shift = i;
						j_shift = j;
						k_shift = k;
						l_shift = l;
						current_cost = cost;
					}
				}
			}

	if(k_shift != l_shift) {
		unsigned value1 = route[i_shift], value2 = route[i_shift + 1];
		if(k_shift > l_shift) {
			route.erase(route.begin() + i_shift);
			route.erase(route.begin() + i_shift);
			route.insert(route.begin() + (j_shift + 1), value2);
			route.insert(route.begin() + (j_shift + 1), value1);
			
			// Updating the position of the intermediate routes
			for(unsigned k = l_shift + 1; k < k_shift; k++) {
				v_pos[k].first += 2;
				v_pos[k].second += 2;
			}
			v_pos[k_shift].first += 2;
			v_pos[l_shift].second += 2;
		} else {
			route.insert(route.begin() + (j_shift + 1), value2);
			route.insert(route.begin() + (j_shift + 1), value1);
			route.erase(route.begin() + i_shift);
			route.erase(route.begin() + i_shift);

			// Updating the position of the intermediate routes
			for(unsigned k = k_shift + 1; k < l_shift; k++) {
				v_pos[k].first -= 2;
				v_pos[k].second -= 2;
			}
			v_pos[k_shift].second -= 2;
			v_pos[l_shift].first -= 2;
		}
		solution neighbor(cars);
		neighbor.set_route(route);
		neighbor.set_vehicles(vehicles);
		neighbor.set_pos(v_pos);
		neighbor.set_cost(current_cost);
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::o_shift_three( solution& p_sol ) {
	// TODO
}

solution neighborhoods::extend_contract( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();
	vector< matrix_2d > rates = cars.get_return_rates();

	if(vehicles.size() <= 1) return p_sol;

	vector< unsigned > route = p_sol.get_route();

	solution current = p_sol;

	// Evaluating all possible extensions
	for(unsigned k = 0; k < vehicles.size(); k++) {
		// If is the last vehicle, it is not possible to change its return place
		if(k < vehicles.size() - 1) {
			vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
			// Checking for the extension of all vertexes of the next vehicle but one
			// NOTE the cost can be recalculated based on the previous iterations
			// Aux variable to calculate the return rate of the last vertex
			unsigned aux = v_pos[k + 1].second;
			if(aux == n) aux = 0;

			double cost = p_sol.get_cost();
			unsigned limit = p_sol.get_trip_size(k + 1) - 1;
			for(unsigned i = 0; i < limit; i++) {

				cost -= distances[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first ] ][ route[ v_pos[k + 1].first + 1 ] ];
				cost -= rates[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first ] ][ route[ aux ] ];
				cost -= rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ v_pos[k].second ] ];
				cost += distances[ vehicles[k].number ][ route[ v_pos[k + 1].first ] ][ route[ v_pos[k + 1].first + 1 ] ];
				cost += rates[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first + 1 ] ][ route[ aux ] ];
				cost += rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ v_pos[k].second + 1 ] ];

				v_pos[k].second++;
				v_pos[k + 1].first++;

				// cout << "Vehicle " << vehicles[k].number << "(" << i << "): " << cost;

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					vector< t_vec > veh(vehicles);
					veh[k].end = route[ v_pos[k].second ];
					veh[k + 1].begin = route[ v_pos[k + 1].first ];
					
					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(veh);
					neighbor.set_pos(v_pos);
					neighbor.set_cost(cost);
					// cout << "Vehicle " << vehicles[k].number << "(" << i << "): " << cost << " - " << neighbor.evaluate() << endl;
					current = neighbor;
				}
				// cout << endl;
			}
		}

		// If is the first vehicle, it is not possible to change its rent place
		if(k > 0) {
			vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
			// Checking for the extension of all vertexes of the previous vehicle but one
			// NOTE the cost can be recalculated based on the previous iterations
			// Aux variable to calculate the return rate of the last vertex
			unsigned aux = v_pos[k].second;
			if(aux == n) aux = 0;

			double cost = p_sol.get_cost();
			unsigned limit = p_sol.get_trip_size(k - 1) - 1;
			for(unsigned i = 0; i < limit; i++) {

				cost -= distances[ vehicles[k - 1].number ][ route[ v_pos[k].first - 1 ] ][ route[ v_pos[k].first ] ];
				cost -= rates[ vehicles[k - 1].number ][ route[ v_pos[k - 1].first ] ][ route[ v_pos[k - 1].second ] ];
				cost -= rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ aux ] ];
				cost += distances[ vehicles[k].number ][ route[ v_pos[k].first - 1 ] ][ route[ v_pos[k].first ] ];
				cost += rates[ vehicles[k - 1].number ][ route[ v_pos[k - 1].first ] ][ route[ v_pos[k - 1].second - 1 ] ];
				cost += rates[ vehicles[k].number ][ route[ v_pos[k].first - 1 ] ][ route[ aux ] ];

				v_pos[k].first--;
				v_pos[k - 1].second--;

				// cout << "Vehicle " << vehicles[k].number << "(" << i << "): " << cost;

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					vector< t_vec > veh(vehicles);
					veh[k].begin = route[ v_pos[k].first ];
					veh[k - 1].end = route[ v_pos[k - 1].second ];

					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(veh);
					neighbor.set_pos(v_pos);
					neighbor.set_cost(cost);
					cout << "Vehicle " << vehicles[k].number << "(" << i << "): " << cost << " - " << neighbor.evaluate() << endl;
					current = neighbor;
				}
				// cout << endl;
			}
		}
	}

	return current;
}

solution neighborhoods::extend_contract_one( solution& p_sol ) {
	unsigned n = cars.get_n();
	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< matrix_2d > distances = cars.get_distances();
	vector< matrix_2d > rates = cars.get_return_rates();

	if(vehicles.size() <= 1) return p_sol;

	vector< unsigned > route = p_sol.get_route();

	solution current = p_sol;

	// Evaluating all possible extensions
	for(unsigned k = 0; k < vehicles.size(); k++) {
		// If is the last vehicle, it is not possible to change its return place
		if(k < vehicles.size() - 1) {
			vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
			// The next vehicle must have more than just one edge
			if((v_pos[k + 1].second - v_pos[k + 1].first) > 1) {

				// Aux variable to calculate the return rate of the last vertex
				unsigned aux = v_pos[k + 1].second;
				if(aux == n) aux = 0;

				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first ] ][ route[ v_pos[k + 1].first + 1 ] ];
				cost -= rates[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first ] ][ route[ aux ] ];
				cost -= rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ v_pos[k].second ] ];
				cost += distances[ vehicles[k].number ][ route[ v_pos[k + 1].first ] ][ route[ v_pos[k + 1].first + 1 ] ];
				cost += rates[ vehicles[k + 1].number ][ route[ v_pos[k + 1].first + 1 ] ][ route[ aux ] ];
				cost += rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ v_pos[k].second + 1 ] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					v_pos[k].second++;
					v_pos[k + 1].first++;
					vector< t_vec > veh(vehicles);
					veh[k].end = route[ v_pos[k].second ];
					veh[k + 1].begin = route[ v_pos[k + 1].first ];

					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(veh);
					neighbor.set_pos(v_pos);
					neighbor.set_cost(cost);
					cout << "Vehicle " << vehicles[k].number << ": " << cost << " - " << neighbor.evaluate() << endl;
					current = neighbor;
				}
			}
		}

		// If is the first vehicle, it is not possible to change its rent place
		if(k > 0) {
			vector< pair< unsigned, unsigned> > v_pos(p_sol.get_pos());
			// The previous vehicle must have more than just one edge
			if((v_pos[k - 1].second - v_pos[k - 1].first) > 1) {

				// Aux variable to calculate the return rate of the last vertex
				unsigned aux = v_pos[k].second;
				if(aux == n) aux = 0;

				double cost = p_sol.get_cost();
				cost -= distances[ vehicles[k - 1].number ][ route[ v_pos[k].first - 1 ] ][ route[ v_pos[k].first ] ];
				cost -= rates[ vehicles[k - 1].number ][ route[ v_pos[k - 1].first ] ][ route[ v_pos[k - 1].second ] ];
				cost -= rates[ vehicles[k].number ][ route[ v_pos[k].first ] ][ route[ aux ] ];
				cost += distances[ vehicles[k].number ][ route[ v_pos[k].first - 1 ] ][ route[ v_pos[k].first ] ];
				cost += rates[ vehicles[k - 1].number ][ route[ v_pos[k - 1].first ] ][ route[ v_pos[k - 1].second - 1 ] ];
				cost += rates[ vehicles[k].number ][ route[ v_pos[k].first - 1 ] ][ route[ aux ] ];

				// If the cost is smaller than the current, the change is applied
				if(cost < current.get_cost()) {
					v_pos[k].first--;
					v_pos[k - 1].second--;
					vector< t_vec > veh(vehicles);
					veh[k].begin = route[ v_pos[k].first ];
					veh[k - 1].end = route[ v_pos[k - 1].second ];

					solution neighbor(cars);
					neighbor.set_route(route);
					neighbor.set_vehicles(veh);
					neighbor.set_pos(v_pos);
					neighbor.set_cost(cost);
					cout << "Vehicle " << vehicles[k].number << ": " << cost << " - " << neighbor.evaluate() << endl;
					current = neighbor;
				}
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
		current.show_data();
		current = extend_contract(current);
		if(current.get_cost() < best.get_cost())
			best = current;
		else {
			// current = i_swap_two(current);
			// current = i_shift_two(current);
			// current = i_swap_one(current);
			// current = o_shift_one(current);
			// current = o_swap_one(current);
			// current = o_swap_two(current);
			current = o_shift_two(current);
			if(current.get_cost() < best.get_cost())
				best = current;
			else is_improved = false;
			// current = two_opt(current);
			// if(current.get_cost() < best.get_cost())
			// 	best = current;
			// else {
			// 	current = swap_one(current);
			// 	if(current.get_cost() < best.get_cost())
			// 		best = current;
			// 	else is_improved = false;
			// }
		}
	}

	return best;
}