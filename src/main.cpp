//============================================================================
// Name        : main.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Main program file
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "../include/FWChrono.h"
#include "../include/logger.h"
#include "../include/mt19937ar.h"
#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/constructor.h"
#include "../include/ils.h"

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

	unsigned long seed = time(NULL);
	if(argc >= 2)
		seed = string_to< unsigned long >(args[1]);
	// time_t seed = time(NULL);
	// srand(seed);
	init_genrand(seed);

	instance cars;
	cars.read_data();

	double alpha = 0.2;
	// unsigned max_it = cars.get_n() + (5 * cars.get_c());
	unsigned max_it = 50;
	unsigned max_ms_it = 10;
	logger logs(timer);
	ils ILS(cars, max_ms_it, max_it, alpha, logs);
	solution best = ILS.execute();
	timer.stop();
	printf("%.2lf;%.2lf;", best.get_cost(), timer.getStopTime());
	// printf("BEST FOUND SOLUTION -- %.2lf:\n", timer.getStopTime());
	// best.show_data();

	// vector< pair< unsigned, unsigned> > pos = best.get_pos();
	// for(unsigned i = 0; i < pos.size(); i++)
	// 	printf("%d %d\n", pos[i].first, pos[i].second);

	if(argc >= 3)
		best.show_latex(args[2], "plot.tex");

	return 0;
}
