#ifndef DEF_BROWNIAN
#define DEF_BROWNIAN

#include <string>
#include <random>
#include <armadillo>

class Brownian {
public:
	Brownian(int m_dimension=10,
			std::string s_correlation="./data/data_correlation.txt");

	arma::vec generate();


private:
	int m_dimension;
	arma::mat m_correlation;
	std::mt19937 m_gen;

};

#endif