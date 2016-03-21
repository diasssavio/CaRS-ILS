//============================================================================
// Name        : solution.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : 
//============================================================================

#include "../include/solution.h"

solution::solution( instance& _cars ) { 
	cars = _cars;
	route = vector< unsigned >(cars.get_n());
	cost = numeric_limits< double >::max();
}

solution::~solution() { }

void solution::set_instance( instance& _cars ) { cars = _cars; }

void solution::set_route( const vector< unsigned >& _route ) { route = _route; }

void solution::set_vehicles( const vector< t_vec >& _vehicles ) { vehicles = _vehicles; }

void solution::set_cost( double _cost ) { cost = _cost; }

instance& solution::get_instance() { return cars; }

const vector< unsigned >& solution::get_route() const { return route; }

const vector< t_vec >& solution::get_vehicles() const { return vehicles; }

double solution::get_cost() { return cost; }

void solution::show_data() {
	unsigned k = 0;
	for(unsigned i = 0; i < cars.get_n(); i++) {
		if(vehicles[k].end == route[i]) k++;
		printf("%4d", vehicles[k].number);
	}
	printf("\n");
	for(unsigned i = 0; i < cars.get_n(); i++)
		printf("%4d", route[i]);
	printf("\nCOST: %.2lf\n", cost);
}

void solution::show_latex( char* filename ) {
	ifstream _file;
	_file.open(filename);
	if(_file.is_open()) {
		ofstream _result;
		_result.open("plot.tex", ios::out);
		if(!_result) return;
		_result << "\\documentclass{standalone}" << endl << "\\usepackage{tikz}" << endl << "\\usetikzlibrary{positioning}" << endl
					 << "\\begin{document}" << endl << "\\begin{tikzpicture}[scale=0.1, every node/.style={scale=0.5,line width=0.5pt}]" << endl;

		char line[256];
		unsigned count = 1;
		bool first = true;
		while(_file.getline(line, 256)) {
			vector< string > values;
			char* block = strtok(line, " ");
			while(block) {
				values.push_back(block);
				block = strtok(NULL, " ");
			}
			if(first) {
				first = false;
				_result << "\\node[draw](" << count << ") at (" << values[1] << "," << values[2] << "){" << count << "};" << endl;	
			} else
				_result << "\\node[draw,circle](" << count << ") at (" << values[1] << "," << values[2] << "){" << count << "};" << endl;
			count++;
		}

		unsigned k = 0;
		string colors[5] = {"red", "black", "blue", "green", "yellow"};
		for(unsigned i = 0; i < cars.get_n() - 1; i++) {
			if(vehicles[k].end == route[i]) k++;
			_result << "\\draw[->,line width=1pt," << colors[k] <<"] (" << route[i] + 1 << ") -- (" << route[i+1] + 1 << ");" << endl;
		}
		_result << "\\draw[->,line width=1pt," << colors[k] <<"] (" << route[cars.get_n() - 1] + 1 << ") -- (" << 1 << ");" << endl;
		
		_result << "\\end{tikzpicture}" << endl << "\\end{document}";
	}
}