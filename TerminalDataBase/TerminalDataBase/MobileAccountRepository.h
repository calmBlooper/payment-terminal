#pragma once

#include "MobileAccount.h"
#include "Repository.h"

#include <string>
#include <utility>

#include "DBConnector.h"

class MobileAccountRepository : public Repository<MobileAccount, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<MobileAccount> data;

	void retrieveData() {
		data.clear();
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			assert(sqlite3_column_count(stmt) == 4);

			const __int64 id = sqlite3_column_int64(stmt, 0);
			const std::string currency = std::string((const char*)sqlite3_column_text(stmt, 1));
			const double balance = sqlite3_column_double(stmt, 2);
			const std::string number = std::string((const char*)sqlite3_column_text(stmt, 3));

			data.push_back(MobileAccount(id, currency, balance, number));
		}
	}

public:
	MobileAccountRepository()
	{
		return;
	};

	~MobileAccountRepository() {
		return;
	};

	virtual MobileAccount getByKey(const std::string& name) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
		rc = sqlite3_prepare_v2(DB_connection, MobileAccountTable::GET.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		rc = sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data.empty() ? MobileAccount() : data.front();
	};

	virtual std::vector<MobileAccount> getAll() {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, MobileAccountTable::SELECT.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data;
	};
	virtual void insert(const MobileAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, MobileAccountTable::INSERT.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);

		rc = sqlite3_bind_text(stmt, 1, entity.getCurrency().c_str(), entity.getCurrency().length(), SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, entity.getBalance());
		rc = sqlite3_bind_text(stmt, 3, entity.getNumber().c_str(), entity.getNumber().length(), SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void remove(const MobileAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, MobileAccountTable::DELETE.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
		rc = sqlite3_bind_int64(stmt, 1, entity.getId());
		rc = sqlite3_step(stmt);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void update(const MobileAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, MobileAccountTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);

		rc = sqlite3_bind_double(stmt, 1, entity.getBalance());
		rc = sqlite3_bind_int64(stmt, 2, entity.getId());

		rc = sqlite3_step(stmt);

		checkSQLError(rc, zErrMsg);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_finalize(stmt);
	};

};