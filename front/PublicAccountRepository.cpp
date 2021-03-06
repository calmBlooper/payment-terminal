#include "PublicAccountRepository.h"

void PublicAccountRepository::retrieveData() {
	data.clear();
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		assert(sqlite3_column_count(stmt) == 5);

		const long long id = sqlite3_column_int64(stmt, 0);
		const std::string currency = std::string((const char*)sqlite3_column_text(stmt, 1));
		const double balance = sqlite3_column_double(stmt, 2);
		const std::string name = std::string((const char*)sqlite3_column_text(stmt, 3));
		const std::string address = std::string((const char*)sqlite3_column_text(stmt, 4));

		data.push_back(PublicAccount(id, currency, balance, name, address));
	}
}

PublicAccountRepository::PublicAccountRepository()
{
	return;
};

PublicAccountRepository::~PublicAccountRepository() {
	return;
};

PublicAccount PublicAccountRepository::getByKey(const std::string& name) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
	rc = sqlite3_prepare_v2(DB_connection, PublicAccountTable::GET.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	rc = sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data.empty() ? PublicAccount() : data.front();
};

std::vector<PublicAccount> PublicAccountRepository::getAll() {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, PublicAccountTable::SELECT.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data;
};

void PublicAccountRepository::insert(const PublicAccount& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, PublicAccountTable::INSERT.c_str(), -1, &stmt, 0);
	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);

	rc = sqlite3_bind_text(stmt, 1, entity.getCurrency().c_str(), entity.getCurrency().length(), SQLITE_STATIC);
	rc = sqlite3_bind_double(stmt, 2, entity.getBalance());
	rc = sqlite3_bind_text(stmt, 3, entity.getName().c_str(), entity.getName().length(), SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 4, entity.getAddress().c_str(), entity.getAddress().length(), SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	checkSQLError(rc, sqlite3_errmsg(DB_connection));

	rc = sqlite3_reset(stmt);
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_finalize(stmt);
};

void PublicAccountRepository::remove(const PublicAccount& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, PublicAccountTable::DELETE.c_str(), -1, &stmt, 0);
	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
	rc = sqlite3_bind_int64(stmt, 1, entity.getId());
	rc = sqlite3_step(stmt);
	checkSQLError(rc, zErrMsg);
	rc = sqlite3_reset(stmt);
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_finalize(stmt);
};

void PublicAccountRepository::update(const PublicAccount& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, PublicAccountTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);

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