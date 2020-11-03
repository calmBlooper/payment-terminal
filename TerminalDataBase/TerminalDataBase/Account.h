#pragma once

#include <string>

class Account {
private:
	const unsigned long id;
	std::string currency;
	unsigned long balance;

public:
	Account() : id(0), balance(0), currency("Any")
	{
		return;
	};

	Account(const unsigned long& id,
		    const std::string& currency = "Any",
		    const unsigned long& balance = 0)
		: id(id),
		currency(currency),
		balance(balance)
	{
		return;
	};

	virtual ~Account() {
		return;
	};

	const unsigned long& getId() const { return id; };
	const unsigned long& getBalance() const { return balance; };
	const std::string& getCurrency() const { return currency; };

	//limit 10 000 ???
	void replenish(const unsigned int& sum)
	{
		balance += sum;
	};
	void dismount(const unsigned int& sum)
	{
		balance = balance >= sum ? balance - sum : 0;
	};
	
};