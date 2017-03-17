//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Iterated Local Search class implementation
//============================================================================

#include "../include/ils.h"

ils::ils( instance& _cars, unsigned _ms_it, unsigned _it, double _alpha, logger* _logs ) : max_it(_it), max_ms_it(_ms_it), alpha(_alpha) {
	this->cars = _cars;
	this->logs = _logs;
}

ils::~ils() { }

void ils::subsets( unsigned i, unsigned n ) {
	if(i > n){
		// printf("%d subsets:",++cont);
    vector< unsigned > aux;
  	for(unsigned j = 1; j <= n; j++)
    	if(conj[j] == 1)
    		aux.push_back(j);
    sets.push_back(aux);
	}else{
  	conj[i] = 1;
  	subsets(i + 1, n);
  	conj[i] = 0;
  	subsets(i + 1, n);
  }
}

solution& ils::execute() {
	constructor cons(cars, alpha);
	neighborhoods neighbors(cars, logs);
	perturbation pert(cars);
	solution sol(cars);

	vector< unsigned > vehicles;
	for(unsigned k = 0; k < cars.get_c(); k++)
		vehicles.push_back(k);

	bool first = true;
	for(unsigned i = 0; i < max_ms_it; i++) {
		sol = cons.generate_sol(vehicles);
		if(first) {
			best = sol;
			first = false;
		}
		for(unsigned k = 0; k < max_it; k++) {
			sol = neighbors.execute(sol);
			if(sol.get_cost() < best.get_cost())
				best = sol;
			if((k + 1) < max_it) {
				sol = pert.execute(sol);
			}
		}
		// Adding the best solution for MS iterations
		logs->make_log(best.get_cost());
	}

	return best;
}

solution& ils::execute_neighborhood( unsigned _i ) {
	constructor cons(cars, alpha);
	neighborhoods neighbors(cars, logs);
	perturbation pert(cars);
	solution sol(cars);

	vector< unsigned > vehicles;
	for(unsigned k = 0; k < cars.get_c(); k++)
		vehicles.push_back(k);

	bool first = true;
	for(unsigned i = 0; i < max_ms_it; i++) {
		sol = cons.generate_sol(vehicles);
		if(first) {
			best = sol;
			first = false;
		}
		for(unsigned k = 0; k < max_it; k++) {
			double ref = sol.get_cost();
			switch (_i) {
				case 0:
					sol = neighbors.o_swap_one(sol);
					break;
				case 1:
					sol = neighbors.o_swap_two(sol);
					break;
				case 2:
					sol = neighbors.o_swap_two_one(sol);
					break;
				case 3:
					sol = neighbors.o_swap_three(sol);
					break;
				case 4:
					sol = neighbors.o_shift_one(sol);
					break;
				case 5:
					sol = neighbors.o_shift_two(sol);
					break;
				case 6:
					sol = neighbors.o_shift_three(sol);
					break;
				case 7:
					sol = neighbors.exchange(sol);
					break;
				case 8:
					sol = neighbors.full_extend_contract(sol);
					break;
				case 9:
					sol = neighbors.i_swap_one(sol);
					break;
				case 10:
					sol = neighbors.i_swap_two(sol);
					break;
				case 11:
					sol = neighbors.i_swap_three(sol);
					break;
				case 12:
					sol = neighbors.i_two_opt(sol);
					break;
				case 13:
					sol = neighbors.i_reverse(sol);
					break;
				case 14:
					sol = neighbors.i_shift_one(sol);
					break;
				case 15:
					sol = neighbors.i_shift_two(sol);
					break;
				case 16:
					sol = neighbors.i_shift_three(sol);
					break;
			}

			if(sol.get_cost() < ref)
				logs->make_individual_log(ref, sol.get_cost());
			if(sol.get_cost() < best.get_cost())
				best = sol;
			if((k + 1) < max_it) {
				sol = pert.execute(sol);
			}
		}
		// Adding the best solution for MS iterations
		logs->make_log(best.get_cost());
	}

	// sol = cons.generate_sol(vehicles);
	// double ref = sol.get_cost();
	// switch (_i) {
	// 	case 0:
	// 		sol = neighbors.o_swap_one(sol);
	// 		break;
	// 	case 1:
	// 		sol = neighbors.o_swap_two(sol);
	// 		break;
	// 	case 2:
	// 		sol = neighbors.o_swap_two_one(sol);
	// 		break;
	// 	case 3:
	// 		sol = neighbors.o_swap_three(sol);
	// 		break;
	// 	case 4:
	// 		sol = neighbors.o_shift_one(sol);
	// 		break;
	// 	case 5:
	// 		sol = neighbors.o_shift_two(sol);
	// 		break;
	// 	case 6:
	// 		sol = neighbors.o_shift_three(sol);
	// 		break;
	// 	case 7:
	// 		sol = neighbors.exchange(sol);
	// 		break;
	// 	case 8:
	// 		sol = neighbors.full_extend_contract(sol);
	// 		break;
	// 	case 9:
	// 		sol = neighbors.i_swap_one(sol);
	// 		break;
	// 	case 10:
	// 		sol = neighbors.i_swap_two(sol);
	// 		break;
	// 	case 11:
	// 		sol = neighbors.i_swap_three(sol);
	// 		break;
	// 	case 12:
	// 		sol = neighbors.i_two_opt(sol);
	// 		break;
	// 	case 13:
	// 		sol = neighbors.i_reverse(sol);
	// 		break;
	// 	case 14:
	// 		sol = neighbors.i_shift_one(sol);
	// 		break;
	// 	case 15:
	// 		sol = neighbors.i_shift_two(sol);
	// 		break;
	// 	case 16:
	// 		sol = neighbors.i_shift_three(sol);
	// 		break;
	// }
	// sol.show_data();
	// if(sol.get_cost() < ref)
	// 	logs->make_individual_log(ref, sol.get_cost());

	return best;
}
