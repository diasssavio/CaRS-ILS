//============================================================================
// Name        : perturbation.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Perturbation class implementation
//============================================================================

#include "../include/perturbation.h"

perturbation::perturbation( instance& _cars ) { this->cars = _cars; }

perturbation::~perturbation() { }

solution perturbation::multiple_shift( solution& p_sol, unsigned max_pert ) {
	int number_pert = 1 + (genrand_int32() % max_pert);

	unsigned n = cars.get_n();
	vector< matrix_2d > distances = cars.get_distances();

	vector< t_vec > vehicles = p_sol.get_vehicles();
	vector< pair< unsigned, unsigned> > v_pos = p_sol.get_pos();
	vector< unsigned > route(p_sol.get_route());

	double cost = p_sol.get_cost();
	while(number_pert > 0) {
		// Raffling the two distinct routes to be perturbed
		unsigned k = genrand_int32() % vehicles.size();
		unsigned l = genrand_int32() % vehicles.size();

		if(k == l) {
			if((l + 1) < vehicles.size()) l++;
			else l--;
		}

		number_pert--;

		// Impossible to shift a route with only the renting places
		if(p_sol.get_trip_size(k) == 1 || p_sol.get_trip_size(l) == 1) continue;

		// Raffling the first element to be shifted & its position
		unsigned i_first = v_pos[k].first + 1 + (genrand_int32() % (p_sol.get_trip_size(k) - 1));
		unsigned j_first = v_pos[l].first + (genrand_int32() % p_sol.get_trip_size(l));

		// Aux variable to calculate the last edge of the cycle
		unsigned aux1 = i_first + 1;
		if(i_first == (n - 1)) aux1 = 0;
		unsigned aux2 = j_first + 1;
		if(j_first == (n - 1)) aux2 = 0;

		// Calculating the current cost for the first shift (k~>l)
		cost -= distances[ vehicles[k].number ][ route[i_first - 1] ][ route[i_first] ];
		cost -= distances[ vehicles[k].number ][ route[i_first] ][ route[aux1] ];
		cost -= distances[ vehicles[l].number ][ route[j_first] ][ route[aux2] ];
		cost += distances[ vehicles[l].number ][ route[j_first] ][ route[i_first] ];
		cost += distances[ vehicles[l].number ][ route[i_first] ][ route[aux2] ];
		cost += distances[ vehicles[k].number ][ route[i_first - 1] ][ route[aux1] ];

		printf("Cost: %.2lf\n", cost);

		// Raffling the second element to be shifted & its position
		unsigned i_second = v_pos[l].first + 1 + (genrand_int32() % (p_sol.get_trip_size(l) - 1));
		unsigned j_second = v_pos[k].first + (genrand_int32() % p_sol.get_trip_size(k));

		// Aux variable to calculate the last edge of the cycle
		unsigned aux3 = i_second + 1;
		if(i_second == (n - 1)) aux3 = 0;
		unsigned aux4 = j_second + 1;
		if(j_second == (n - 1)) aux4 = 0;

		// Calculating the current cost for the second shift (l~>k)
		if(j_second == i_first) {
			cost -= distances[ vehicles[k].number ][ route[j_second - 1] ][ route[aux4] ];
			cost += distances[ vehicles[k].number ][ route[j_second - 1] ][ route[i_second] ];
			cost += distances[ vehicles[k].number ][ route[i_second] ][ route[aux4] ];
		} else if((j_second + 1) == i_first) {
			cost -= distances[ vehicles[k].number ][ route[j_second] ][ route[aux1] ];
			cost += distances[ vehicles[k].number ][ route[j_second] ][ route[i_second] ];
			cost += distances[ vehicles[k].number ][ route[i_second] ][ route[aux1] ];
		} else {
			cost -= distances[ vehicles[k].number ][ route[j_second] ][ route[aux4] ];
			cost += distances[ vehicles[k].number ][ route[j_second] ][ route[i_second] ];
			cost += distances[ vehicles[k].number ][ route[i_second] ][ route[aux4] ];
		}
		if(j_first == i_second) {
			cost -= distances[ vehicles[l].number ][ route[i_second] ][ route[i_first] ];
			cost -= distances[ vehicles[l].number ][ route[i_second - 1] ][ route[i_second] ];
			cost += distances[ vehicles[l].number ][ route[i_second - 1] ][ route[i_first] ];
		} else if((j_first + 1) == i_second) {
			cost -= distances[ vehicles[l].number ][ route[i_first] ][ route[i_second] ];
			cost -= distances[ vehicles[l].number ][ route[i_second] ][ route[aux3] ];
			cost += distances[ vehicles[l].number ][ route[i_first] ][ route[aux3] ];
		} else {
			cost -= distances[ vehicles[l].number ][ route[i_second] ][ route[aux3] ];
			cost -= distances[ vehicles[l].number ][ route[i_second - 1] ][ route[i_second] ];
			cost += distances[ vehicles[l].number ][ route[i_second - 1] ][ route[aux3] ];
		}

		// Applying the changes on the route
		unsigned value1 = route[i_first], value2 = route[i_second];
		printf("%d<~>%d: %d~>%d \t %d~>%d\n", k, l, i_first, j_first, i_second, j_second);
		if(k > l) {
			route.insert(route.begin() + (j_second + 1), value2);
			route.insert(route.begin() + (j_first + 1), value1);
			if(j_second >= i_first) route.erase(route.begin() + i_first + 1);
			else route.erase(route.begin() + i_first + 2);
		} else {
			route.insert(route.begin() + (j_first + 1), value1);
			route.insert(route.begin() + (j_second + 1), value2);
			if(j_second >= i_first) route.erase(route.begin() + i_first);
			else route.erase(route.begin() + i_first + 1);
		}
		if(j_first >= i_second) route.erase(route.begin() + i_second);
		else route.erase(route.begin() + i_second + 1);
	}

	solution neighbor(cars);
	neighbor.set_route(route);
	neighbor.set_vehicles(vehicles);
	neighbor.set_pos(v_pos);
	neighbor.set_cost(cost);

	return neighbor;
}

solution perturbation::multiple_swap( solution& p_sol, unsigned max_pert ) {
	unsigned number_pert = 1 + (genrand_int32() % max_pert);
}

solution perturbation::vehicle_swap( solution& p_sol ) {

}

solution perturbation::double_bridge( solution& p_sol ) {

}

solution perturbation::execute( solution& p_sol ) {
	
}