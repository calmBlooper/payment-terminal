#include <utility>

#ifndef CURRENCY
namespace Currency {
	const char* UAH = "UAH";
	const char* EUR = "EUR";
	const char* USD = "USD";
}
#define CURRENCY
#endif

const std::pair<double, const char*> convert(const double& amount, const char* from, const char* to) {
	double result = amount;
	// some conversion magic here
	return {result,to};
}