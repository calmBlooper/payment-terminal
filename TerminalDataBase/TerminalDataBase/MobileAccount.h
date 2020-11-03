#pragma once

#include "Account.h"

class MobileAccount : Account {
private:
	const std::string telephoneNumber;

public:
	MobileAccount(const unsigned long& id,
		          const std::string& number)
		: Account(id),
		  telephoneNumber(number) 
	{
		return;
	};

	~MobileAccount() {
		return;
	};

	const std::string& getNumber() const { return telephoneNumber; };
};