#include "EWalletAccountRepository.h"

void EWalletAccountRepository::retrieveData() {
	data.clear();
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		assert(sqlite3_column_count(stmt) == 5);

		const long long id = sqlite3_column_int64(stmt, 0);
		const std::string currency = std::string((const char*)sqlite3_column_text(stmt, 1));
		const double balance = sqlite3_column_double(stmt, 2);
		const std::string login = std::string((const char*)sqlite3_column_text(stmt, 3));
		const std::string email = std::string((const char*)sqlite3_column_text(stmt, 4));

		data.push_back(EWalletAccount(id, currency, balance, login, email));
	}
}

EWalletAccountRepository::EWalletAccountRepository()
{
	return;
};

EWalletAccountRepository::~EWalletAccountRepository() {
	return;
};

EWalletAccount EWalletAccountRepository::getByKey(const std::pair<std::string, std::string>& loginEmail) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
	rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::GET_BY_LOGIN_EMAIL.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	rc = sqlite3_bind_text(stmt, 1, loginEmail.first.c_str(), loginEmail.first.length(), SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 2, loginEmail.second.c_str(), loginEmail.second.length(), SQLITE_STATIC);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data.empty() ? EWalletAccount() : data.front();
};

std::vector<EWalletAccount> EWalletAccountRepository::getAll() {
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

void EWalletAccountRepository::insert(const EWalletAccount& entity) {
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

void EWalletAccountRepository::remove(const EWalletAccount& entity) {
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

void EWalletAccountRepository::update(const EWalletAccount& entity) {
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

EWalletAccount EWalletAccountRepository::getByLogin(const std::string& login) {
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

EWalletAccount EWalletAccountRepository::getByEmail(const std::string& email) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
	rc = sqlite3_prepare_v2(DB_connection, EWalletAccountTable::GET_BY_EMAIL.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	rc = sqlite3_bind_text(stmt, 1, email.c_str(), email.length(), SQLITE_STATIC);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data.empty() ? EWalletAccount() : data.front();
};