//============================================================================
// Name        : main.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>

#include "../include/FWChrono.h"
#include "../include/mt19937ar.h"
#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/constructor.h"

using namespace std;

template<typename T>
T string_to(const string& s){
	istringstream i(s);
	T x;
	if (!(i >> x)) return 0;
	return x;
}

int main(int argc, char* args[]) {
	FWChrono timer;
	timer.start();
	// time_t seed = time(NULL);
	unsigned long seed = string_to<unsigned long>(args[1]);
	// srand(seed);
	init_genrand(seed);

	instance cars;
	cars.read_data();

	constructor cons(cars, 0.5);
	vector< unsigned > cars_set;
	for(unsigned k = 0; k < cars.get_c(); k++)
		cars_set.push_back(k);
	solution sol = cons.generate_sol(cars_set);

	vector< unsigned > route;
	for(unsigned i = 0; i < cars.get_n(); i++) route.push_back(i);
	vector< t_vec > vehicles;
	for(unsigned k = 0; k < cars.get_c(); k++) {
		t_vec aux;
		aux.number = k;
		aux.begin = k * (cars.get_n() / cars.get_c());
		aux.end = (k + 1) * (cars.get_n() / cars.get_c());
		vehicles.push_back(aux);
	}
	
	sol.show_data();

	/*int max_iterations = 0.1 * n;
	int max_r = max_iterations / 2;
	double alpha_2 = 0.2;

	// ils ILS(instance, max_iterations, p, r, timer);
	ils ILS(instance, max_iterations, max_r, alpha_2, p, r, timer);
	solution result = ILS.execute();

	timer.stop();
	// printf("TOTAL EXECUTION TIME: %.2lf", timer.getStopTime());
	printf("%.2lf,", timer.getStopTime());
	// result.show_data();

	// printf("\nIT_LOG:\n");
	vector< pair< double, unsigned> > it_log = ILS.get_it_log();
	vector< double > times = ILS.get_times();
	double min_time = 0.0;
	for(unsigned i = 0; i < it_log.size(); i++){
		// printf("#%d:\t%.2lf\t%.2lf\n", it_log[i].second, it_log[i].first, times[i]);

		if(it_log[i].first == result.get_total_cost() && min_time == 0.0)
			min_time = times[i];
	}

	printf("%.2lf,%.2lf\n", min_time, result.get_total_cost());
	// cout << "," << seed << endl;*/

	if(argc == 3) {
		sol.show_latex(args[2]);
	}

	return 0;
}
