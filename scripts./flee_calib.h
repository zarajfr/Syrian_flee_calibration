#ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include "simulator.h"
#include "openga.hpp"

struct MySolution{
	double a0;
	double a1;
	double a2;
	double b0;
	double b1;
	double d1;

	std::string to_string() const
	{
		return
			"{a0:"+std::to_string(a0)+
			", a1:"+std::to_string(a1)+
			", a2:"+std::to_string(a2)+
			", b0:"+std::to_string(b0)+
			", b1:"+std::to_string(b1)+
			", d1:"+std::to_string(d1)+
			"}";
	}
};
struct MyMiddleCost{
	std::vector< std::vector<double > > simout;
};

typedef EA::Genetic<MySolution,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution,MyMiddleCost> Generation_Type;

void init_genes(MySolution& p,const std::function<double(void)> &rnd01);
bool eval_solution(const MySolution& p, MyMiddleCost &c);
MySolution mutate(const MySolution& X_base,const std::function<double(void)> &rnd01,double shrink_scale);
MySolution crossover(const MySolution& X1,const MySolution& X2,const std::function<double(void)> &rnd01);

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X);
void SO_report_generation(int generation_number, const EA::GenerationType<MySolution,MyMiddleCost> &last_generation, const MySolution& best_genes);

#endif
