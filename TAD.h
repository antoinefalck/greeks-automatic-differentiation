#ifndef DEF_TAD
#define DEF_TAD

#include <cmath>
#include "Brownian.h"

class TAD {
public:
	TAD(int dimension=10,
		std::string s_correlation="./data/data_correlation.txt",
		double m_maturity=1,
		double m_strike=100,
		std::string s_spot="./data/data_spot.txt",
		std::string s_weight="./data/data_weight.txt",
		std::string s_sigma="./data/data_sigma.txt",
		double m_interest_rate=0.1);

	double generate(arma::vec coefficients);
	double bump(arma::vec coefficients);

private:
	Brownian m_brownian;
	double m_maturity;
	double m_strike;
	arma::vec m_spot;
	arma::vec m_weight;
	arma::vec m_sigma;
	double m_interest_rate;

};

#endif