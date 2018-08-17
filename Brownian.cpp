#include "Brownian.h"

using namespace std;
using namespace arma;

Brownian::Brownian(int dimension,
					string s_correlation): m_dimension(dimension) {

	m_correlation.load(s_correlation, raw_ascii);

	random_device rd;
	mt19937 gen(rd());
	m_gen = gen;
}

vec Brownian::generate() {
	normal_distribution<double> normal_density(0, 1);

	vec Z(m_dimension);
	for (int i = 0; i < m_dimension; ++i) {
		Z[i] = normal_density(m_gen);
	}

	mat T(m_correlation);
	T = chol(T, "lower");

	return T*Z;
}