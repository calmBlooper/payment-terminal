#pragma once

#include "Account.h"

class EWalletAccount : Account {
private:
	std::string login;
	std::string email;

public:
	EWalletAccount(): Account(), login(""), email("")
	{
		return;
	};

	EWalletAccount(const unsigned long& id,
		           const std::string& login,
		           const std::string& email)
		: Account(id),
		  login(login),
		  email(email)
	{
		return;
	};

	~EWalletAccount() {
		return;
	};

	const std::string& getLogin() const { return login; };
	const std::string& getEmail() const { return email; };

	void setLogin(const std::string& login)
	{
		(*this).login = login;
		return;
	};
	void setEmail(const std::string& email)
	{
		(*this).email = email;
		return;
	};

};