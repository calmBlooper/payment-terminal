#pragma once

#include "Paycard.h"
#include "Repository.h"

#include <string>
#include <utility>
#include <assert.h>
#include <iostream>

#include "DBConnector.h"

class PaycardRepository : public Repository<Paycard, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<Paycard> data;

	void retrieveData() {
		data.clear();
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			assert(sqlite3_column_count(stmt) == 7);

			const __int64 id = sqlite3_column_int64(stmt, 0);
			const __int64 accId = sqlite3_column_int64(stmt, 1);
			const std::string number = std::string((const char*)sqlite3_column_text(stmt, 2));
			const __int32 cvv = sqlite3_column_int(stmt, 3);
			const __int32 expMonth = sqlite3_column_int(stmt, 4);
			const __int32 expYear = sqlite3_column_int(stmt, 5);
			const __int32 pin = sqlite3_column_int(stmt, 6);

			data.push_back(Paycard(id, accId, number, cvv, expMonth, expYear, pin));
		}
	}

public:
	PaycardRepository()
	{
		return;
	};

	~PaycardRepository() {
		return;
	};

	void checkSQLError(const int rc, char* zErrMsg) {
		if (rc != SQLITE_OK && rc != SQLITE_DONE) {
			std::cout << rc << std::endl;
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Operation completed successfully\n");
		}
	}

	void checkSQLError(const int rc, const char* zErrMsg) {
		if (rc != SQLITE_OK && rc != SQLITE_DONE) {
			std::cout << rc << std::endl;
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		}
		else {
			fprintf(stdout, "Operation completed successfully\n");
		}
	}

	virtual Paycard getByKey(const std::string& name) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
		rc = sqlite3_prepare_v2(DB_connection, PaycardTable::GET.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		rc = sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data.empty() ? Paycard() : data.front();
	};

	virtual std::vector<Paycard> getAll() {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, PaycardTable::SELECT.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data;
	};
	virtual void insert(const Paycard& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, PaycardTable::INSERT.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);

		rc = sqlite3_bind_int64(stmt, 1, entity.getAccountId());
		rc = sqlite3_bind_text(stmt, 2, entity.getCardNumber().c_str(), entity.getCardNumber().length(), SQLITE_STATIC);
		rc = sqlite3_bind_int(stmt, 3, entity.getCvv());
		rc = sqlite3_bind_int(stmt, 4, entity.getExpMonth());
		rc = sqlite3_bind_int(stmt, 5, entity.getExpYear());
		rc = sqlite3_bind_int(stmt, 6, entity.getPin());

		rc = sqlite3_step(stmt);
		checkSQLError(rc, sqlite3_errmsg(DB_connection));

		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void remove(const Paycard& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, PaycardTable::DELETE.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
		rc = sqlite3_bind_int64(stmt, 1, entity.getId());
		rc = sqlite3_step(stmt);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void update(const Paycard& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, PaycardTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);

		rc = sqlite3_bind_int(stmt, 1, entity.getPin());
		rc = sqlite3_bind_int64(stmt, 2, entity.getId());

		rc = sqlite3_step(stmt);

		checkSQLError(rc, zErrMsg);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_finalize(stmt);
	};

};