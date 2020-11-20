#pragma once

#include "Account.h"

class MobileAccount : public Account {
private:
	const std::string telephoneNumber;

public:
	MobileAccount(const std::string& number = "") : Account(), telephoneNumber(number)
	{
		return;
	};

	MobileAccount(const std::string& currency,
		const double& initialBalance,
		const std::string& number)
		: Account(0, currency, initialBalance),
		telephoneNumber(number)
	{
		return;
	};

	MobileAccount(const long long& id,
		const std::string& currency,
		const double& initialBalance,
		const std::string& number)
		: Account(id, currency, initialBalance),
		telephoneNumber(number)
	{
		return;
	};

	~MobileAccount() {
		return;
	};

	const std::string& getNumber() const { return telephoneNumber; };
};

std::ostream& operator<<(std::ostream&, const MobileAccount&);