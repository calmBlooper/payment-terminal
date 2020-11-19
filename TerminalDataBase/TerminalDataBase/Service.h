#pragma once

#include <iostream>
#include <string>

#include "Identifiable.h"

class Service : Identifiable {
private:
	const long long id;
	const int serviceType;
	const std::string name;
	const double commission;
	
public:
	Service(const int& serviceType = 0,
		    const std::string& name = "",
		    const double& commission = 0.0)
		: id(0),
		serviceType(serviceType),
		name(name),
		commission(commission)
	{
		return;
	};

	Service(const long long& id,
		    const int& serviceType,
		    const std::string& name,
		    const double& commission)
		: id(id),
		  serviceType(serviceType),
		  name(name),
		  commission(commission)
	{
		return;
	};

	~Service()
	{
		return;
	};

	virtual const long long& getId() const { return id; };
	const int& getServiceType() const { return serviceType; };
	const std::string& getName() const { return name; };
	const double& getCommission() const { return commission; };

};

std::ostream& operator<<(std::ostream&, const Service&);