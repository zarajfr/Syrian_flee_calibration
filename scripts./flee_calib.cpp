#include "example_mo1.h"

void init_genes(MySolution& p,const std::function<double(void)> &rnd01)
{
	p.a0 = 0.5*rnd01();
	p.a1 = 0.5*rnd01();
	p.a2 = 0.5*rnd01();
	p.b0 = 2.0*rnd01();
	p.b1 = 2.0*rnd01();
	p.d1 = 3.0*rnd01();
}

bool eval_solution(const MySolution& p,MyMiddleCost &c)
{
	double a0 = p.a0;
	double a1 = p.a1;
	double a2 = p.a2;
	double b0 = p.b0;
	double b1 = p.b1;
	double d1 = p.d1;
	simulator* s = new simulator(a0,a1,a2,b0,b1,d1);
	s->populate();
	s->read_data();
	c.simout = s->run();
	s->~simulator();

	return true; // genes are accepted
}

MySolution mutate(const MySolution& X_base,const std::function<double(void)> &rnd01,double shrink_scale)
{
	MySolution X_new;
	bool in_range_a0,in_range_a1, in_range_b0, in_range_b1, in_range_a2, in_range_d1;
	do{
		X_new=X_base;
		X_new.a0+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a1+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a2+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.b0+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.b1+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.d1+=0.2*(rnd01()-rnd01())*shrink_scale;

		in_range_a0= (X_new.a0>=0.0 && X_new.a0<0.5);
		in_range_a1= (X_new.a1>=0.0 && X_new.a1<0.5);
		in_range_a2= (X_new.a2>=0.0 && X_new.a2<0.5);
		in_range_b0= (X_new.b0>=0.0 && X_new.b0<2.0);
		in_range_b1= (X_new.b1>=0.0 && X_new.b1<2.0);
		in_range_d1= (X_new.d1>=0.0 && X_new.d1<3.0);

	} while( !in_range_a1 || !in_range_a0 || !in_range_b0 || !in_range_a2 || !in_range_d1 || !in_range_b1 );
	return X_new;
}

MySolution crossover(const MySolution& X1,const MySolution& X2,const std::function<double(void)> &rnd01)
{
	MySolution X_new;
	double r;
	r=rnd01();
	X_new.a0=r*X1.a0+(1.0-r)*X2.a0;
	r=rnd01();
	X_new.a1=r*X1.a1+(1.0-r)*X2.a1;
	r=rnd01();
	X_new.b0=r*X1.b0+(1.0-r)*X2.b0;
	r=rnd01();
	X_new.b1=r*X1.b1+(1.0-r)*X2.b1;
	r=rnd01();
	X_new.a2=r*X1.a2+(1.0-r)*X2.a2;
	r=rnd01();
	X_new.d1=r*X1.d1+(1.0-r)*X2.d1;

	return X_new;
}

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X)
{
	double fitnesscore = 0.0;
	double denom = 0.0;
		for(int i = 0; i< X.middle_costs.simout.size(); i++)
			for(int j =0; j<X.middle_costs.simout[i].size();j++)
			{
				denom += X.middle_costs.simout[i][j];
			}
		fitnesscore = denom;
		return fitnesscore;
	// finalize the cost
}


void SO_report_generation(int generation_number, const EA::GenerationType<MySolution,MyMiddleCost> &last_generation, const MySolution& best_genes)
{
	std::ofstream output_file;
	output_file.open("./bin/result_so1.txt", std::ios::app);
	std::cout
		<<"Generation ["<<generation_number<<"], "
		<<"Best="<<last_generation.best_total_cost<<", "
		<<"Average="<<last_generation.average_cost<<", "
		<<"Best genes=("<<best_genes.to_string()<<")"<<", "
		<<"Exe_time="<<last_generation.exe_time
		<<std::endl;

	output_file
		<<"Generation ["<<generation_number<<"], "
		<<"Best="<<last_generation.best_total_cost<<", "
		<<"Average="<<last_generation.average_cost<<", "
		<<"Best genes=("<<best_genes.to_string()<<")"<<", "
		<<"Exe_time="<<last_generation.exe_time
		<<std::endl;


	output_file.close();

}
