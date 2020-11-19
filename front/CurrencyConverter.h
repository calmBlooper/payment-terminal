#pragma once
#include <utility>

namespace Currency {
	const char* UAH() { return "UAH"; };
	const char* EUR() { return "EUR"; };
	const char* USD() { return "USD"; };
}

const std::pair<double, const char*> convert(const double& amount, const char* from, const char* to) {
	double result = amount;
	// some conversion magic here
	return { result,to };
}