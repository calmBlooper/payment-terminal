#pragma once

#include "Repository.h"
#include "EWalletAccount.h"

class EWalletAccountRepository : public Repository<EWalletAccount, std::pair<std::string, std::string>> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<EWalletAccount> data;

	void retrieveData();

public:
	EWalletAccountRepository();
	~EWalletAccountRepository();

	virtual EWalletAccount getByKey(const std::pair<std::string, std::string>& loginEmail);
	virtual std::vector<EWalletAccount> getAll();
	virtual void insert(const EWalletAccount& entity);
	virtual void remove(const EWalletAccount& entity);
	virtual void update(const EWalletAccount& entity);

	EWalletAccount getByLogin(const std::string& login);
	EWalletAccount getByEmail(const std::string& email);

};