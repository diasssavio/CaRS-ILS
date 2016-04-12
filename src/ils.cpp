//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Iterated Local Search class implementation
//============================================================================

#include "../include/ils.h"

ils::ils( instance& _cars, unsigned _it, double _alpha, logger& _logs ) : max_it(_it), alpha(_alpha) {
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
	neighborhoods neighbors(cars);
	perturbation pert(cars);
	solution sol(cars);

	subsets(1, cars.get_c());
	bool first = true;
	for(unsigned i = 0; i < sets.size() - 1; i++) {
		printf("{");
		for(unsigned j = 0; j < sets[i].size(); j++)
			printf("%d ", --sets[i][j]);
		printf("\b}\n");
		if(sets[i].size() >= 2) {
			sol = cons.generate_sol(sets[i]);
			if(first) {
				best = sol;
				first = false;
			}
			// sol.show_latex("BrasilRJ14e.coo", "cons.tex");
			sol.show_data();
			for(unsigned k = 0; k < 2; k++) {
				sol = neighbors.execute(sol);
				if(sol.get_cost() < best.get_cost())
					best = sol;
				sol.show_data();
				sol = pert.multiple_shift(sol, 1);
				sol.show_data();
				vector< pair< unsigned, unsigned> > pos = sol.get_pos();
				for(unsigned i = 0; i < pos.size(); i++)
					printf("%d->%d\n", pos[i].first, pos[i].second);
			}
		}
	}

	return best;
}