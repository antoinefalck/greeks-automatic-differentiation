#include "MC.h"

using namespace std;
using namespace arma;

MC::MC(function<double()> generation,
		double precision,
		function<double()> batch): m_generation(generation),
									m_precision(precision),
									m_batch(batch) {
}

int MC::get_number_simulation() {
	int const N(1000);

	double mean(0.0), variance(0.0), gen;
	for (int i = 0; i < N; ++i) {
		gen = m_generation();
		mean += gen;
		variance += gen*gen;
	}

	mean /= N;
	variance = variance/N - N/(N-1)*mean*mean;

	int number_simulation;
	number_simulation = 8*variance/m_precision/m_precision;
	if(number_simulation==0) {
		number_simulation = 1;
	}
	return number_simulation;
}

double MC::compute() {
	int number_simulation;
	number_simulation = get_number_simulation();

	double sum(0.0);
	for (int i = 0; i < number_simulation; ++i) {
		sum += m_generation();
	}

	return sum/number_simulation;
}

double MC::get_lambda() {
	int const N(1000);

	double var(0.0), cov(0.0), gen1, gen2;
	for (int i = 0; i < N; ++i)	{
		gen1 = m_generation();
		gen2 = m_batch();
		var += (gen1-gen2)*(gen1-gen2);
		cov += gen1*(gen1-gen2);
	}

	var /= N;
	cov /= N;

	return cov/var;
}

double MC::batch() {
	int number_simulation;
	double lambda;
	number_simulation = get_number_simulation();
	lambda = get_lambda();

	double sum(0.0);
	for (int i = 0; i < number_simulation; ++i) {
		sum += (1-lambda)*m_generation()+lambda*m_batch();
	}

	return sum/number_simulation;
}