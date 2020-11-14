#pragma once

#include "Account.h"

class EWalletAccount : public Account {
private:
	const std::string login;
	const std::string email;

public:
	EWalletAccount(const std::string& login = "", const std::string& email = "") : Account(), login(login), email(email)
	{
		return;
	};

	EWalletAccount(const std::string& currency,
		const double& initialBalance,
		const std::string& login,
		const std::string& email)
		: Account(0, currency, initialBalance),
		login(login),
		email(email)
	{
		return;
	};

	EWalletAccount(const __int64& id,
		const std::string& currency,
		const double& initialBalance,
		const std::string& login,
		const std::string& email)
		: Account(id, currency, initialBalance),
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

};

std::ostream& operator<<(std::ostream& out, const EWalletAccount& ewa) {
	return out << "id-" << ewa.getId() << ":" << ewa.getBalance() << ewa.getCurrency() << ',' << ewa.getLogin() << ',' << ewa.getEmail() << std::endl;
}