#pragma once

#include <string>
#include <iostream>

#include "Identifiable.h"

class Account : public Identifiable {
private:
	const long long id;
	const std::string currency;
	double balance;

public:
	Account() : id(0), currency("UAH"), balance(0.0)
	{
		return;
	};

	Account(const long long& id,
		    const std::string& currency = "UAH",
		    const double& balance = 0.0)
		: id(id),
		currency(currency),
		balance(balance)
	{
		return;
	};

	virtual ~Account() {
		return;
	};

	virtual const long long& getId() const { return id; };
	const double& getBalance() const { return balance; };
	const std::string& getCurrency() const { return currency; };

	void replenish(const double& amount, const char* from)
	{
		balance += amount;
	};
	void dismount(const double& amount, const char* from)
	{
		balance = balance >= amount ? balance - amount : 0.0;
	};
	
};