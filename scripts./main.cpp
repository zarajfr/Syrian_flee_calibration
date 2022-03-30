#include <string>
#include <iostream>
#include <fstream>
#include "simulator.h"
// #include "ga_destination.h"
#include "example_mo1.h"
#include "openga.hpp"

int main()
{
	//SO
	EA::Chronometer timer;
	timer.tic();
	GA_Type ga_obj;
	ga_obj.problem_mode= EA::GA_MODE::SOGA;
	// ga_obj.multi_threading=true;
	ga_obj.multi_threading=false;
	ga_obj.idle_delay_us=1; // switch between threads quickly
	ga_obj.verbose=false;
	ga_obj.population=40;
	ga_obj.generation_max=1000;
	ga_obj.calculate_SO_total_fitness=calculate_SO_total_fitness;
	ga_obj.init_genes= init_genes;
	ga_obj.eval_solution= eval_solution;
	ga_obj.mutate= mutate;
	ga_obj.crossover= crossover;
	ga_obj.SO_report_generation= SO_report_generation;
	ga_obj.best_stall_max=10;
	ga_obj.elite_count=10;
	ga_obj.crossover_fraction=0.45;
	ga_obj.mutation_rate=0.3;
	std::cout<<"N_thread:  "<< ga_obj.N_threads << std::endl;
	ga_obj.solve();

	// simulator* s = new simulator(0.000176, 0.000254, 0.037154, 0.182069, 0.027112, 2.750529);
	// simulator* s = new simulator(0.000005, 0.000138, 0.059255, 0.137101, 0.088437, 2.892504); // best = Best=3.95416
	// simulator* s = new simulator(0.000051, 0.326790, 0.352455, 0.069421, 0.139680, 1.585801); // Best=3.98366
	// simulator* s = new simulator(0.000000, 0.000000, 0.000000, 0.104212, 0.087418, 2.665873);
	// simulator* s = new simulator(0.000508, 0.615801, 0.071985, 0.315580, 0.100000, 2.090424); //n0-het
	// s->populate();
	// s->read_data();
	// s->run();
	// s->approximate_flee();
	// std::vector< std::vector<double> > v = s->pass_output_data();
	// s->~simulator();
	// std::ofstream output_file2;
	// output_file2.open("simres-no-het.csv");
	// for(int i = 0; i  < v.size(); i++){
	// 	for(int j = 0; j< v[i].size(); j++){
	// 		double a = v[i][j]; //population_resolution
	// 		output_file2 << a << ',';
	// 	}
	// 	output_file2 << '\n';
	// }
	// output_file2.close();


	return 0;
}
