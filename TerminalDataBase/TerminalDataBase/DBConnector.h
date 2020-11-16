#pragma once

#include <sqlite3.h>
#include <string>

#include "AccountTable.h"
#include "ServiceTable.h"
#include "PaycardTable.h"

class DBConnector
{
private:
	static DBConnector* connector;
	sqlite3* connection;
	const char* dir;

    DBConnector(const char* path) : connection(nullptr), dir(path)
    {
		init();
		return;
    }
	
	~DBConnector() {
		if (connection) {
			closeConnection();
		}
		return;
	}

	void init() {
		if (sqlite3_open(dir, &connection)) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(connection));
		}
		else {
			fprintf(stdout, "Opened database successfully\n");
		}
	}

public:
    DBConnector(DBConnector& other) = delete;
    void operator=(const DBConnector&) = delete;
	
	static DBConnector* InitConnection(const char* path);
    static DBConnector* GetInstance();


    sqlite3*  getConnection() const {
        return connection;
    }

	void closeConnection() const {
		if (sqlite3_close(connection)) {
			fprintf(stderr, "Error while closing database: %s\n", sqlite3_errmsg(connection));
		}
		else {
			fprintf(stdout, "Closed database successfully\n");
		}
	}

};

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
