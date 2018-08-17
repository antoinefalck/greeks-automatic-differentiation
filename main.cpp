#include <iostream>
#include <armadillo>
#include <string>
#include <functional>

#include "Brownian.h"
#include "TAD.h"
#include "MC.h"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {

	if(argc!=2) {
		cout << "Error: usage is ./main <precision>" << endl;
		return 1;
	}


	TAD T, U;
	
	vec a;
	a.zeros(11);
	a(1) = 1;			// Pour dériver par rapport à s_0^1
	// a(0) = 1;			// Pour dériver par rapport à r


	function<double()> f = bind(&TAD::generate, T, a);
	function<double()> g = bind(&TAD::bump, U, a);


	MC M(f,atof(argv[1]),g);
	cout << "Tangent Automatic Differentiation Method\n---------------------" << endl;
	cout << "Nb simulation needed\t" << M.get_number_simulation() << endl;
	cout << "Monte Carlo simulation\t" << M.compute() << endl << endl;

	MC N(g,atof(argv[1]));
	cout << "Bump Method\n---------------------" << endl;
	cout << "Nb simulation needed\t" << N.get_number_simulation() << endl;
	cout << "Monte Carlo simulation\t" << N.compute() << endl << endl;

	cout << "Variance Reduction (batch method)\n---------------------" << endl;
	cout << "Lambda\t\t\t" << M.get_lambda() << endl;
	cout << "Monte Carlo simulation\t" << M.batch() << endl << endl;

	return 0;
}
