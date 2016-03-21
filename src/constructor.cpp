//============================================================================
// Name        : constructor.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include "../include/constructor.h"

constructor::constructor( instance& _cars, double _alpha ) : alpha(_alpha) {
	cars = _cars;
	double value = 0.0;
	while(value <= 1.7) {
		gamma.push_back(value);
		value += 0.05;
	}
}

constructor::~constructor() { }

solution constructor::generate_sol( vector< unsigned >& allowed_cars ) {
	unsigned n = cars.get_n();
	unsigned c = cars.get_c();
	vector< matrix_2d > distances = cars.get_distances();
	vector< matrix_2d > return_rates = cars.get_return_rates();

	// Solution data
	vector< unsigned > route;
	vector< t_vec > vehicles;
	double cost = 0.0;

	// Selecting number of nodes for each vehicle
	// TODO Randomize the weights of the vehicles
	vector< unsigned > weights(c);
	// unsigned value = n - c;
	for(unsigned k = 0; k < c - 1; k++) {
		weights[k] = n/c;
		// value -= weights[k];
		printf("%4d", weights[k]);
	}
	weights[c - 1] = ceil(n/c);
	printf("%4d\n", weights[c - 1]);

	// Mounting the initial tour
	unsigned rent_place = 0;
	route.push_back(rent_place);
	vector< unsigned > CL;
	for(unsigned i = 1; i < n; i++)
		CL.push_back(i);

	while((allowed_cars.size() > 0) && (CL.size() > 0)) {
		// Adding rent_place to route
		vector< unsigned > trip;
		trip.push_back(rent_place);
		// CL.erase(find(CL.begin(), CL.end(), rent_place));

		// Raffling the car to the trip
		unsigned chosen_i = genrand_int32() % allowed_cars.size();
		unsigned chosen = allowed_cars[chosen_i];
		unsigned no_counter = 1;
		matrix_2d distances_c = distances[chosen];
		matrix_2d rates_c = return_rates[chosen];

		// Creating RCL based on return rates
		vector< unsigned > RCL;
		if(allowed_cars.size() == 1)
			RCL.push_back(0);
		else {
			// Checking for return points, except the rented and visited ones
			double min_value = rates_c[rent_place][ CL[0] ], max_value = rates_c[rent_place][ CL[0] ];
			for(unsigned i = 1; i < CL.size(); i++) {
				if(min_value > rates_c[rent_place][ CL[i] ])
					min_value = rates_c[rent_place][ CL[i] ];
				if(max_value < rates_c[rent_place][ CL[i] ])
					max_value = rates_c[rent_place][ CL[i] ];
			}
			// Mounting the RCL from the CL based on alpha parameter (GRASP inspired)
			for(unsigned i = 0; i < CL.size(); i++)
				if(rates_c[rent_place][ CL[i] ] <= (min_value + alpha * (max_value - min_value)))
					RCL.push_back(CL[i]);
		}

		// Selecting return point
		unsigned return_place = RCL[ genrand_int32() % RCL.size() ];
		t_vec aux;
		aux.number = chosen;
		aux.begin = rent_place;
		aux.end = return_place;
		cost += rates_c[rent_place][return_place];

		// Removing return_place from the CL
		if(return_place)
			CL.erase(find(CL.begin(), CL.end(), return_place));

		cout << aux.number << ": " << rent_place << "~>" << return_place << endl;

		// Mounting the route based on chosen car
		while(CL.size() > 0) {
			if(no_counter == weights[chosen_i]) {
				trip.push_back(return_place);
				cost += distances_c[ trip[trip.size() - 1] ][return_place];
				break;
			}

			// Evaluating the position for insertion of all elements in CL
			unsigned next_point, next_pos, cl_pos;
			double next_cost = numeric_limits<double>::max(), gamma_value;
			for(unsigned i = 0; i < CL.size(); i++) {
				gamma_value = gamma[genrand_int32() % gamma.size()] * (distances_c[rent_place][ CL[i] ] + distances_c[ CL[i] ][return_place]);
				if(trip.size() == 1) { // If the trip is empty (only rent_place is in)
					double g_k = distances_c[rent_place][ CL[i] ] - gamma_value;
					if(g_k < next_cost) {
						next_point = CL[i];
						cl_pos = i;
						next_pos = 1;
						next_cost = g_k;
					}
				// } else if(CL[i] == return_place) { // If the point is the return_place, then it can be only inserted in the end
				// 	double g_k = distances_c[ trip[trip.size() - 1] ][return_place] - gamma_value;
				// 	if(g_k < next_cost) {
				// 		next_point = CL[i];
				// 		cl_pos = i;
				// 		next_pos = trip.size();
				// 		next_cost = g_k;
				// 	}
				} else { // Insertion on the middle of the trip
					for(unsigned j = 1; j < trip.size(); j++) {
						double g_k = distances_c[ trip[j - 1] ][ CL[i] ] + distances_c[ CL[i] ][ trip[j] ] - distances_c[ trip[j - 1] ][ trip[j] ] - gamma_value;
						if(g_k < next_cost) {
							next_point = CL[i];
							cl_pos = i;
							next_pos = j;
							next_cost = g_k;
						}
					}
					// Evaluate insertion on the end of the trip
					double g_k = distances_c[ trip[trip.size() - 1] ][ CL[i] ] - gamma_value;
					if(g_k < next_cost) {
						next_point = CL[i];
						cl_pos = i;
						next_pos = trip.size();
						next_cost = g_k;
					}
				}
			}

			cout << next_point << ":\t";

			// Check next_pos for insertion of next_point & removing it from CL
			if(trip.size() == 1) {
				trip.push_back(next_point);
				cost += distances_c[rent_place][next_point];
				CL.erase(CL.begin() + cl_pos);
			} else {
				if(next_pos == trip.size()) { // If insertion on the end
					trip.push_back(next_point);
					cost += distances_c[ trip[next_pos - 1] ][next_point];
				} else {
					trip.insert(trip.begin() + next_pos, next_point);
					cost += distances_c[ trip[next_pos - 1] ][next_point] + distances_c[next_point][ trip[next_pos] ] - distances_c[ trip[next_pos - 1] ][ trip[next_pos] ];
				}
				CL.erase(CL.begin() + cl_pos);	
			}

			for(unsigned k = 0; k < trip.size(); k++)
				printf("%4d", trip[k]);
			printf("\n");

			no_counter++;
			// if(next_point == return_place) break;
		}

		if(CL.size() == 0) {
			trip.push_back(return_place);
			cost += distances_c[ trip[trip.size() - 1] ][return_place];
		}

		// Removing the used car from allowed_cars
		allowed_cars.erase(allowed_cars.begin() + chosen_i);
		rent_place = return_place;

		// Adding trip from car to total route
		vehicles.push_back(aux);
		for(unsigned i = 1; i < trip.size(); i++) {
			route.push_back(trip[i]);
			printf("%4d", trip[i]);
		}
		printf("\n");
	}

	solution result(cars);
	result.set_route(route);
	result.set_vehicles(vehicles);
	result.set_cost(cost);

	return result;
}