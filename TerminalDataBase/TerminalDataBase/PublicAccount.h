#pragma once

#include "Account.h"

class PublicAccount : Account {
private:
	std::string name;
	std::string address;

public:
	PublicAccount(): Account(), name(""), address("")
	{
		return;
	};

	PublicAccount(const unsigned long& id,
		          const std::string& name = "",
		          const std::string& address = "")
		: Account(id),
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

	void setName(const std::string& name)
	{
		(*this).name = name;
		return;
	};
	void setAddress(const std::string& address)
	{ 
		(*this).address = address;
		return;
	};

};