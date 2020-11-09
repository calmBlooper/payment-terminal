#pragma once

#pragma once

#include "EWalletAccount.h"
#include "Repository.h"

#include <string>
#include <utility>

#include "DBConnector.h"

class EWalletAccountRepository : public Repository<EWalletAccount, std::string> {
private:
	sqlite3_stmt* stmt = 0;
	std::vector<EWalletAccount> data;

	void retrieveData() {
		data.clear();
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			assert(sqlite3_column_count(stmt) == 5);

			const __int64 id = sqlite3_column_int64(stmt, 0);
			const std::string currency = std::string((const char*)sqlite3_column_text(stmt, 1));
			const double balance = sqlite3_column_double(stmt, 2);
			const std::string login = std::string((const char*)sqlite3_column_text(stmt, 3));
			const std::string email = std::string((const char*)sqlite3_column_text(stmt, 4));

			data.push_back(EWalletAccount(id, currency, balance, login, email));
		}
	}

public:
	EWalletAccountRepository()
	{
		return;
	};

	~EWalletAccountRepository() {
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

	virtual EWalletAccount getByKey(const std::string& login) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
		rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::GET_BY_LOGIN.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		rc = sqlite3_bind_text(stmt, 1, login.c_str(), login.length(), SQLITE_STATIC);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data.empty() ? EWalletAccount() : data.front();
	};

	virtual std::vector<EWalletAccount> getAll() {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::SELECT.c_str(), -1, &stmt, 0);

		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
		retrieveData();
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_reset(stmt);
		rc = sqlite3_finalize(stmt);

		return data;
	};
	virtual void insert(const EWalletAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::INSERT.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);

		rc = sqlite3_bind_text(stmt, 1, entity.getCurrency().c_str(), entity.getCurrency().length(), SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, entity.getBalance());
		rc = sqlite3_bind_text(stmt, 3, entity.getLogin().c_str(), entity.getLogin().length(), SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 4, entity.getEmail().c_str(), entity.getEmail().length(), SQLITE_STATIC);

		rc = sqlite3_step(stmt);

		checkSQLError(rc, sqlite3_errmsg(DB_connection));

		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void remove(const EWalletAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::DELETE.c_str(), -1, &stmt, 0);
		rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
		rc = sqlite3_bind_int64(stmt, 1, entity.getId());
		rc = sqlite3_step(stmt);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_reset(stmt);
		rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

		checkSQLError(rc, zErrMsg);

		rc = sqlite3_finalize(stmt);
	};

	virtual void update(const EWalletAccount& entity) {
		char* zErrMsg = 0;
		int rc = 0;
		sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

		rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);

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