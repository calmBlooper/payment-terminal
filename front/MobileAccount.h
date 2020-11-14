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

	MobileAccount(const __int64& id,
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

std::ostream& operator<<(std::ostream& out, const MobileAccount& pa) {
	return out << "id-" << pa.getId() << ":" << pa.getBalance() << pa.getCurrency() << ',' << pa.getNumber() << std::endl;
}