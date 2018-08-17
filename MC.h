#ifndef DEF_MC
#define DEF_MC

#include <functional>
#include <armadillo>
#include "TAD.h"


class MC {
public:
	MC(std::function<double()> m_generation,
		double m_precision,
		std::function<double()> m_batch=[](){return 0.0;});
	double compute();
	int get_number_simulation();
	double get_lambda();
	double batch();

private:
	std::function<double()> m_generation;
	double m_precision;
	std::function<double()> m_batch;

};

#endif