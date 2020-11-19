#include "DBConnector.h"

DBConnector* DBConnector::connector = nullptr;
DBConnector* DBConnector::InitConnection(const char* path)
{
	if (connector == nullptr)
	{
		connector = new DBConnector(path);
		return connector;
	}
	else if (connector->dir == path)
	{
		return connector;
	}
	else return nullptr;
}
DBConnector* DBConnector::GetInstance()
{
	if (connector == nullptr) {
		DBConnector::InitConnection("test.db");
	}
	return connector;
}