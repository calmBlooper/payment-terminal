#pragma once

#include "Repository.h"
#include "PublicAccount.h"

class PublicAccountRepository : public Repository<PublicAccount, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<PublicAccount> data;

	void retrieveData();

public:
	PublicAccountRepository();
	~PublicAccountRepository();

	virtual PublicAccount getByKey(const std::string& name);
	virtual std::vector<PublicAccount> getAll();
	virtual void insert(const PublicAccount& entity);
	virtual void remove(const PublicAccount& entity);
	virtual void update(const PublicAccount& entity);

};