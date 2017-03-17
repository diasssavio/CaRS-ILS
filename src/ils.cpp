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

	// logs.print_log();

	/*subsets(1, cars.get_c());
	for(unsigned i = 0; i < sets.size() - 1; i++) {
		// printf("{");
		for(unsigned j = 0; j < sets[i].size(); j++)
			--sets[i][j];
			// printf("%d ", --sets[i][j]);
		// printf("\b}\n");
		if(sets[i].size() >= cars.get_c()) {
			for(unsigned l = 0; l < max_ms_it; l++) {
				sol = cons.generate_sol(sets[i]);
				if(first) {
					best = sol;
					first = false;
				}
				// sol.show_latex("BrasilRJ14e.coo", "cons.tex");
				// printf("INITIAL SOLUTION:\n");
				// sol.show_data();
				for(unsigned k = 0; k < max_it; k++) {
					// printf("RVND:\n");
					sol = neighbors.execute(sol);
					// sol = neighbors.full_extend_contract(sol);
					// sol = neighbors.extend_contract(sol);
					if(sol.get_cost() < best.get_cost())
						best = sol;
					// sol.show_data();
					if((k + 1) < max_it) {
						// printf("PERTURBATION:\n");
						sol = pert.execute(sol);
						// sol.show_data();
					}
					// vector< pair< unsigned, unsigned> > pos = sol.get_pos();
          // vector< t_vec > veh = sol.get_vehicles();
					// for(unsigned m = 0; m < pos.size(); m++)
						// printf("%d: %d (%d) -> %d (%d)\n", veh[m].number, pos[m].first, veh[m].begin, pos[m].second, veh[m].end);
				}
			}
		}
	}*/

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
