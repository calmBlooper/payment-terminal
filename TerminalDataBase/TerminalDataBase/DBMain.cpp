#include <iostream>
#include <sqlite3.h>
#include <string>

#include "Account.h"
#include "EWalletAccount.h"
#include "MobileAccount.h"
#include "Paycard.h"
#include "PrivateAccount.h"
#include "PublicAccount.h"
#include "Service.h"

//DB TEST
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(void)
{
	//DB TEST
	const char* dir = "DB\\test.db";
	sqlite3* DB;
	int exit = 0;
	char* zErrMsg = 0;
	const char* data = "Callback function called";

	/* Open database */
	exit = sqlite3_open(dir, &DB);

	if (exit) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
		return(0);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}

	/* Create Table SQL statement */
	const char* sql_create = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";

	/* Execute SQL statement */
	exit = sqlite3_exec(DB, sql_create, callback, 0, &zErrMsg);

	if (exit != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
	
	/* Insert data SQL statement */
	const char* sql_insert = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	/* Execute SQL statement */
	exit = sqlite3_exec(DB, sql_insert, callback, 0, &zErrMsg);

	if (exit != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}

	/* Select data SQL statement */
	const char* sql_select = "SELECT * from COMPANY";

	/* Execute SQL statement */
	exit = sqlite3_exec(DB, sql_select, callback, (void*)data, &zErrMsg);

	if (exit != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	/* Create Update merged SQL statement */
	const char* sql_update = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
		"SELECT * from COMPANY";

	/* Execute SQL statement */
	exit = sqlite3_exec(DB, sql_update, callback, (void*)data, &zErrMsg);

	if (exit != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	/* Create Delete merged SQL statement */
	const char* sql_delete = "DELETE from COMPANY where ID=2; " \
		"SELECT * from COMPANY";

	/* Execute SQL statement */
	exit = sqlite3_exec(DB, sql_delete, callback, (void*)data, &zErrMsg);

	if (exit != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	sqlite3_close(DB);

	std::cout << "Hello DataBase !!!" << std::endl;

	return 0;
}