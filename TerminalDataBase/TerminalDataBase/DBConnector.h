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

	DBConnector(const char* path);
	~DBConnector();

	void init();

public:
    DBConnector(DBConnector& other) = delete;
    void operator=(const DBConnector&) = delete;
	
	static DBConnector* InitConnection(const char* path);
    static DBConnector* GetInstance();

	sqlite3* getConnection() const;
	void closeConnection() const;

};