#include "TAD.h"

using namespace std;
using namespace arma;

TAD::TAD(int dimension,
		string s_correlation,
		double maturity,
		double strike,
		string s_spot,
		string s_weight,
		string s_sigma,
		double interest_rate): m_maturity(maturity),
								m_strike(strike),
								m_interest_rate(interest_rate) {
	
	Brownian brownian(dimension, s_correlation);
	m_brownian = brownian;

	m_spot.load(s_spot, raw_ascii);
	m_weight.load(s_weight, raw_ascii);
	m_sigma.load(s_sigma, raw_ascii);

}

double TAD::generate(vec coefficient) {
	double d_interest_rate(coefficient(0));
	vec d_spot(coefficient.n_elem-1);
	for (uword i = 0; i < (coefficient.n_elem-1); ++i) {
		d_spot(i) = coefficient(i+1);
	}

	vec equity, d_equity;
	equity = m_spot % exp((m_interest_rate-pow(m_sigma,2)/2)*m_maturity + sqrt(m_maturity)*m_sigma%m_brownian.generate());
	d_equity = equity/m_spot%d_spot + m_maturity*d_interest_rate*equity;

	double weighted_equity, d_weighted_equity;
	weighted_equity = accu(m_weight % equity);
	d_weighted_equity = accu(m_weight % d_equity);

	double discount, d_discount;
	discount = exp(-m_interest_rate*m_maturity);
	d_discount = -m_maturity*discount*d_interest_rate;

	double price, d_price;
	price = max(weighted_equity-m_strike, 0.0);
	d_price = 0.0;
	if(price > 0) {
		d_price = d_weighted_equity;
	}

	// double dicounted_price, d_dicounted_price;
	// dicounted_price = discount * price;
	double d_dicounted_price;
	d_dicounted_price = price*d_discount + discount*d_price;

	return d_dicounted_price;
}

double TAD::bump(vec coefficient) {
	double delta(0.01);
	double d_interest_rate = m_interest_rate + coefficient(0)*delta;
	vec d_spot(coefficient.n_elem-1);
	for (uword i = 0; i < (coefficient.n_elem-1); ++i) {
		d_spot(i) = m_spot(i) + coefficient(i+1)*delta;
	}

	vec brownian = m_brownian.generate();
	vec equity, d_equity;
	equity = m_spot % exp((m_interest_rate-pow(m_sigma,2)/2)*m_maturity + sqrt(m_maturity)*m_sigma%brownian);
	d_equity = d_spot % exp((d_interest_rate-pow(m_sigma,2)/2)*m_maturity + sqrt(m_maturity)*m_sigma%brownian);

	double weighted_equity, d_weighted_equity;
	weighted_equity = accu(m_weight % equity);
	d_weighted_equity = accu(m_weight % d_equity);

	double discount, d_discount;
	discount = exp(-m_interest_rate*m_maturity);
	d_discount = exp(-d_interest_rate*m_maturity);

	double price, d_price;
	price = max(weighted_equity-m_strike, 0.0);
	d_price = max(d_weighted_equity-m_strike, 0.0);

	double discounted_price, d_dicounted_price;
	discounted_price = price * discount;
	d_dicounted_price = d_price * d_discount;

	return (d_dicounted_price - discounted_price)/delta;
}