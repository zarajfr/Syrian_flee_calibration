#ifndef __simulatorr__
#define __simulatorr__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <random>
#include <string>
#include <cstdlib>
#include "graph.h"
#include "agent.h"
#include <time.h>
#include <limits>

//she keeps track of time, she runs the agents, updates them, she does the God's job!
class simulator{

public:
	simulator(double alpha0,double alpha1,double alpha2, double beta0, double beta1,double d1);
	// simulator( double pp1, double alpha1, double alpha2, double alpha3);
	simulator(const simulator& s);
	simulator& operator=(const simulator& a);
	~simulator();
	void populate();
	void read_data();
	std::vector< std::vector<double> > pass_output_data();
	std::vector< std::vector<int> > approximate_flee();
	std::vector< std::vector< double> >run();
	// std::vector< std::vector < double > > run();

private:
	std::vector<int> size_pop;
	int simlen;
	graph* net;
	std::vector<agent*> agents;
	//FLEE
	double a0;
	double a1;
	double a2;
	double b0;
	double b1;
	double d1;
	std::vector<double> aggregate_data;
	//destination flow
	// double p1;
	// double a1;
	// double a2;
	// double a3;
	std::vector< std::vector<double> > real_data;
	std::vector< std::vector<double> > output_data;
	double population_resolution;
};

#endif
