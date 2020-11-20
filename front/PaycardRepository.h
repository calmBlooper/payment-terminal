#pragma once

#include "Repository.h"
#include "Paycard.h"

class PaycardRepository : public Repository<Paycard, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<Paycard> data;

	void retrieveData();

public:
	PaycardRepository();
	~PaycardRepository();

	virtual Paycard getByKey(const std::string& name);
	virtual std::vector<Paycard> getAll();
	virtual void insert(const Paycard& entity);
	virtual void remove(const Paycard& entity);
	virtual void update(const Paycard& entity);

};