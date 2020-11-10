#pragma once

#include <string>

#include "Identifiable.h"

class Service : Identifiable {
private:
	const __int64 id;
	const __int32 serviceType;
	const std::string name;
	const double commission;
	
public:
	Service(const __int32& serviceType = 0,
		    const std::string& name = "",
		    const double& commission = 0.0)
		: id(0),
		serviceType(serviceType),
		name(name),
		commission(commission)
	{
		return;
	};

	Service(const __int64& id,
		    const __int32& serviceType,
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

	virtual const __int64& getId() const { return id; };
	const __int32& getServiceType() const { return serviceType; };
	const std::string& getName() const { return name; };
	const double& getCommission() const { return commission; };

};

std::ostream& operator<<(std::ostream& out, const Service& s) {
	return out << "id-" << s.getId() << ":" << s.getName() << '('<< s.getServiceType() << ")," << s.getCommission() << '%'<< std::endl;
}