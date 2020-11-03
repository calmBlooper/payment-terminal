#pragma once

#include <string>

class Service {
private:
	const unsigned long id;
	std::string name;
	double commission;
	
public:
	Service(const unsigned long& id,
		    const std::string& name = "",
		    const double& commission = 0.0)
		: id(0),
		  name(name),
		  commission(commission)
	{
		return;
	};

	~Service()
	{
		return;
	};

	const unsigned long& getId() const { return id; };
	const std::string& getName() const { return name; };
	const double& getCommission() const { return commission; };

	void setName(const std::string& name)
	{
		(*this).name = name;
		return;
	};

	void setCommission(const double& commission)
	{
		(*this).commission = commission;
		return;
	};

};