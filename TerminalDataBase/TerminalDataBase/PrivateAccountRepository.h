#pragma once

#include "Repository.h"
#include "PrivateAccount.h"

class PrivateAccountRepository : public Repository<PrivateAccount, std::pair<std::string,std::string>> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<PrivateAccount> data;

	void retrieveData();

public:
	PrivateAccountRepository();
	~PrivateAccountRepository();

	virtual PrivateAccount getByKey(const std::pair<std::string, std::string>& nameSurename);
	virtual std::vector<PrivateAccount> getAll();
	virtual void insert(const PrivateAccount& entity);
	virtual void remove(const PrivateAccount& entity);
	virtual void update(const PrivateAccount& entity);

	PrivateAccount getById(const long long& id);

};