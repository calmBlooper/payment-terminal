#pragma once

#include "Repository.h"
#include "Service.h"

class ServiceRepository : public Repository<Service, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<Service> data;

	void retrieveData();

public:
	ServiceRepository();
	~ServiceRepository();

	virtual Service getByKey(const std::string& name);
	virtual std::vector<Service> getAll();
	virtual void insert(const Service& entity);
	virtual void remove(const Service& entity);
	virtual void update(const Service& entity);

	std::vector<Service> getByType(const int type);

};