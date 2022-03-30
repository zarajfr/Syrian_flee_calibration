#include "simulator.h"

simulator::simulator(double alpha0,double alpha1,double alpha2, double beta0, double beta1,double dd1){
	// simulator::simulator( double pp1, double alpha1, double alpha2, double alpha3){
	simlen = 40; //default

	// static const int arr[] = { 92000, 44200, 19900, 24000, 31800, 25400, 35200, 29200, 25500, 1700, 18300, 56600, 7200, 15700};
	static const int arr[] = { 23000, 11050, 4975, 6000, 7950, 6350, 8800, 7300, 6375, 425, 4575, 14150, 1800, 3925};
	std::vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	size_pop = v;

	net = new graph(26);
	std::ifstream dfile;
  dfile.open("combined-distances.csv");
  SYR_Gen(net, dfile);
	dfile.close();

	std::ifstream cfile;
  cfile.open("conflict.csv");
  net->SetConflict(cfile);
	cfile.close();

  std::ifstream fwdfile2;
  fwdfile2.open("avgwage.csv");
	net->SetAvgWage(fwdfile2);
	fwdfile2.close();

	std::ifstream fwdfile3;
  fwdfile3.open("fpfhospitalsoverall.csv");
	net->SetHospitals(fwdfile3);
	fwdfile3.close();

	std::ifstream borderfile;
	borderfile.open("computed_finalborder.csv");
	// borderfile.open("scenario3_finalborder.csv");
	net->SetBorder(borderfile);
	borderfile.close();

	std::ifstream f5;
	f5.open("orig_aid.csv");
	net->SetAids(f5);
	f5.close();

	net->SetCamps();

  net->Normalize();

	// p1 = pp1;
	// a1 = alpha1;
	// a2 = alpha2;
	// a3 = alpha3;
	a0 = alpha0;
	a1 = alpha1;
	a2 = alpha2;
	b0 = beta0;
	b1 = beta1;
	d1 = dd1;
	// population_resolution = 50.0; //default
	population_resolution = 200.0; //default
}
simulator::simulator(const simulator& s){
	simlen = s.simlen;
	size_pop = s.size_pop;
	net = s.net;
	agents = s.agents;
	// p1 = s.p1;
	// a1 = s.a1;
	// a2 = s.a2;
	// a3 = s.a3;
	a0 = s.a0;
	a1 = s.a1;
	a2 = s.a2;
	b0 = s.b0;
	b1 = s.b1;
	d1 = s.d1;

	real_data = s.real_data;
	aggregate_data = s.aggregate_data;
	output_data = s.output_data;
	population_resolution = s.population_resolution;
}
simulator& simulator::operator=(const simulator& s){
	if(this==&s) return *this;
		simlen = s.simlen;
		size_pop = s.size_pop;
		net = s.net;
		agents = s.agents;
		// p1 = s.p1;
		// a1 = s.a1;
		// a2 = s.a2;
		// a3 = s.a3;
		a0 = s.a0;
		a1 = s.a1;
		a2 = s.a2;
		b0 = s.b0;
		b1 = s.b1;
		d1 = s.d1;

		real_data = s.real_data;
		aggregate_data = s.aggregate_data;
		output_data = s.output_data;
		population_resolution = s.population_resolution;
		return *this;
}

simulator::~simulator(){
	int x = agents.size();
	for(int i = 0; i<x; i++){
		delete agents[i];
	}
	net->~graph();
}

void simulator::populate(){ //create agents with id and governoarte based on a given vector of size 14 of pop in govs
	int ncounter = 0;
	for(int i = 0; i<size_pop.size() ; i++){
		for(int j = 0; j< size_pop[i]; j++){
			agent* a = new agent(ncounter, i, net);
			agents.push_back(a);
			ncounter++;
		}
	}
}

void simulator::read_data(){

	static const double arr[] = { 2170.0,188572.0,28955.0,36515.0,9227.0,4350.0,2216.0,728.0,6675.0,21266.0,11700.0,50368.0,41436.0,56760.0,60218.0,25967.0,1194.0,58860.0,57382.0,792.0,101199.0,44580.0,108482.0,65269.0,58312.0,65556.0,37149.0,24981.0,9656.0,505.0,1836.0,85.0,18857.0,23104.0,19351.0,15115.0,18789.0,4235.0,7522.0,0.0,130.0,11308.0};
		std::vector<double> refugee_counts (arr, arr + sizeof(arr) / sizeof(arr[0]) );
		std::ifstream f;
		f.open("nlf.csv");
		if(!f.is_open()) std::cout << "File is not open!" << "\n";

		std::vector<std::vector<double> > total_flow_counts(14, std::vector<double>(42, 0.0));
		for(int i  = 0; i<14; i++){
			for(int j = 0; j<42; j++){
				std::string dummy;
				double idp;
				std::getline(f,dummy,',');
				idp = std::stod(dummy);
				total_flow_counts[i][j] = idp;
			}
		}
		f.close();
		// real_data = total_flow_counts;

		std::vector<double> flowpermonth;
		for(int i = 0; i<42; i++){
			double x = 0.0;
			for(int j = 0; j<14; j++){
				x += total_flow_counts[j][i];
			}
			flowpermonth.push_back(x);
		}

		for(int i = 0; i<14; i++){
			std::vector<double> dv;
			real_data.push_back(dv);
			for(int j = 0; j<42; j++){
				double x = total_flow_counts[i][j] + refugee_counts[j]*double(total_flow_counts[i][j])/double(flowpermonth[j]);
				// std::cout<<"division by zero problem"<<x<<std::endl;
				real_data[i].push_back(x);
			}
		}

		for(int i =0; i <42; i++){
			double idp=0.0;
			for(int j =0; j<14;j++){
				idp += total_flow_counts[j][i];
			}
			refugee_counts[i] += idp;
		}
		aggregate_data = refugee_counts;

	// destination flow
	// std::ifstream f;
	// f.open("finaldestinationflow.csv");
	// // std::vector< std::vector<double> > rd;
	// for(int i  = 0; i<18; i++){
	// 	std::vector<double> v;
	// 	for(int j = 0; j<42; j++){
	// 		std::string dummy;
	// 		double idp;
	// 		std::getline(f,dummy,',');
	// 		idp = std::stod(dummy);
	// 		v.push_back(idp);
	// 	}
	// 	rd.push_back(v);
	// }
	// f.close();
}


std::vector< std::vector<double> > simulator::pass_output_data(){return output_data;}


std::vector< std::vector<int> > simulator::approximate_flee(){
	std::vector< std::vector<int> > estimation;
	for(int i =0; i<14; i++){
		std::vector<int> flee_from_i;
		for(int j =0; j<simlen; j++){
			double total_utility = b0*net->nodes[i]->conflict[j+10] + b1*net->nodes[i]->conflict[j+9] - ( a0*net->nodes[i]->avgwage[j] + a1*net->nodes[i]->camps + a2*net->nodes[i]->aids[j] ) ;
			if(total_utility<0) total_utility = 0.0;
			double flee_p = double(total_utility)/double(d1 + total_utility);
			int expected = flee_p*size_pop[i];
			flee_from_i.push_back(expected);
		}
		estimation.push_back(flee_from_i);
	}
	return estimation;
}

std::vector< std::vector < double > > simulator::run(){

	std::vector< std::vector<double> > fleeflow(14, std::vector<double>(simlen, 0.0));
	std::vector< std::vector<double> > dflow(18, std::vector<double>(simlen, 0.0));
	std::vector<std::vector<int> > flee_approximation = approximate_flee();
	//
	// // std::vector<int> leaving_community;
	// for(int t = 0; t<simlen; t++){
	// 	std::vector<int> leaving_community_t;
	// 	for(int i = 0; i<14; i++){
	// 		//no randomisation required now
	// 		if(flee_approximation[i][t]!=0){
	// 			int j=0;
	// 			while(j<flee_approximation[i][t]){
	// 				int selected = rand() % size_pop[i];
	// 				for(int k =0; k<i; k++){selected += size_pop[k];}
	// 				if(leaving_community_t.size()==0){
	// 					if(agents[selected]->get_loc() == i){
	// 						leaving_community_t.push_back(selected);
	// 						j++;
	// 					}
	// 				}
	// 				else if(std::find(leaving_community_t.begin(), leaving_community_t.end(), selected)==leaving_community_t.end() && agents[selected]->get_loc() == i){
	// 						leaving_community_t.push_back(selected);
	// 						j++;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	for(int i = 0; i<leaving_community_t.size(); i++){
	// 		fleeflow[agents[leaving_community_t[i]]->get_loc()][t] += 1;
	// 		// agents[leaving_community_t[i]]->leave(t, 0.242958, 0.826445, 0.419660, 0.819212);
	// 		// //destination
	// 		// // agents[i]->leave(t, p1,a1,a2,a3);
	// 		// if(agents[leaving_community_t[i]]->get_loc()<14) dflow[agents[leaving_community_t[i]]->get_loc()][t] += 1;
	// 		// else if (agents[leaving_community_t[i]]->get_loc() < 17) dflow[14][t] += 1;
	// 		// else if (agents[leaving_community_t[i]]->get_loc() < 22) dflow[15][t] += 1;
	// 		// else if (agents[leaving_community_t[i]]->get_loc() < 25) dflow[16][t] += 1;
	// 		// else if (agents[leaving_community_t[i]]->get_loc() < 26) dflow[17][t] += 1;
	// 	}
	// }
	// //calibrating flee
	//
	// output_data = fleeflow;
	std::vector<std::vector<double> > discrepancy(14, std::vector<double>(42, 0.0));
	for(int i =0;i<14;i++){
		for(int j = 0;j<simlen;j++){
			discrepancy[i][j] = abs(-0.005 + double(flee_approximation[i][j])/double(size_pop[i]) - real_data[i][j]/double(size_pop[i]*population_resolution));
		}
	}
	return discrepancy;

