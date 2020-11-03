#pragma once

#include "Account.h"

class PrivateAccount : Account {
private:
	std::string name;
	std::string surename;

public:
	PrivateAccount(): Account(), name(""), surename("")
	{
		return;
	};

	PrivateAccount(const unsigned long& id,
		           const std::string& name = "",
		           const std::string& surename = "")
		: Account(id),
		  name(name), 
		  surename(surename)
	{
		return;
	};

	~PrivateAccount() {
		return;
	};

	const std::string& getName() const { return name; };
	const std::string& getSurename() const { return surename; };

	void setName(const std::string& name)
	{
		(*this).name = name;
		return;
	};
	void setSurename(const std::string& surename)
	{
		(*this).surename = surename;
		return;
	};

};