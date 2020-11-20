#pragma once

#include "Account.h"

class PublicAccount : public Account {
private:
	const std::string name;
	const std::string address;

public:
	PublicAccount(const std::string& name = "", const std::string& address = "") : Account(), name(name), address(address)
	{
		return;
	};

	PublicAccount(const std::string& currency,
		const double& initialBalance,
		const std::string& name,
		const std::string& address)
		: Account(0, currency, initialBalance),
		name(name),
		address(address)
	{
		return;
	};

	PublicAccount(const long long& id,
		const std::string& currency,
		const double& initialBalance,
		const std::string& name,
		const std::string& address)
		: Account(id, currency, initialBalance),
		name(name),
		address(address)
	{
		return;
	};

	~PublicAccount()
	{
		return;
	};

	const std::string& getAddress() const { return address; };
	const std::string& getName() const { return name; };

};

std::ostream& operator<<(std::ostream&, const PublicAccount&);