#pragma once

#include <string>
#include <iostream>
#include <assert.h>

#include "Identifiable.h"
#include "CurrencyConverter.h"

class Account : public Identifiable {
private:
	const __int64 id;
	const std::string currency;
	double balance;

public:
	Account() : id(0), currency(Currency::UAH), balance(0.0)
	{
		return;
	};

	Account(const __int64& id,
		const std::string& currency = Currency::UAH,
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

	virtual const __int64& getId() const { return id; };
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