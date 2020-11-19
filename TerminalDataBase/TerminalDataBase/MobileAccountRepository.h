#pragma once

#include "Repository.h"
#include "MobileAccount.h"

class MobileAccountRepository : public Repository<MobileAccount, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<MobileAccount> data;

	void retrieveData();

public:
	MobileAccountRepository();
	~MobileAccountRepository();

	virtual MobileAccount getByKey(const std::string& name);
	virtual std::vector<MobileAccount> getAll();
	virtual void insert(const MobileAccount& entity);
	virtual void remove(const MobileAccount& entity);
	virtual void update(const MobileAccount& entity);

};