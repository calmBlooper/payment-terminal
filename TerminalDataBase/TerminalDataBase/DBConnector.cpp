#include "DBConnector.h"

DBConnector::DBConnector(const char* path) : connection(nullptr), dir(path)
{
	init();
	return;
}

DBConnector::~DBConnector() {
	if (connection) {
		closeConnection();
	}
	return;
}

void DBConnector::init() {
	if (sqlite3_open(dir, &connection)) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(connection));
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}
}

sqlite3* DBConnector::getConnection() const {
	return connection;
}

void DBConnector::closeConnection() const {
	if (sqlite3_close(connection)) {
		fprintf(stderr, "Error while closing database: %s\n", sqlite3_errmsg(connection));
	}
	else {
		fprintf(stdout, "Closed database successfully\n");
	}
}

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