#include "ServiceRepository.h"

void ServiceRepository::retrieveData() {
	data.clear();
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		assert(sqlite3_column_count(stmt) == 4);

		const long long id = sqlite3_column_int64(stmt, 0);
		const std::string name = std::string((const char*)sqlite3_column_text(stmt, 1));
		const double commission = sqlite3_column_double(stmt, 2);
		const int serviceType = sqlite3_column_int(stmt, 3);

		data.push_back(Service(id, serviceType, name, commission));
	}
}

ServiceRepository::ServiceRepository()
{
	return;
};

ServiceRepository::~ServiceRepository() {
	return;
};

Service ServiceRepository::getByKey(const std::string& name) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::GET.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	rc = sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data.empty() ? Service() : data.front();
};

std::vector<Service> ServiceRepository::getAll() {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::SELECT.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data;
};

void ServiceRepository::insert(const Service& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::INSERT.c_str(), -1, &stmt, 0);
	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);

	rc = sqlite3_bind_text(stmt, 1, entity.getName().c_str(), entity.getName().length(), SQLITE_STATIC);
	rc = sqlite3_bind_double(stmt, 2, entity.getCommission());
	rc = sqlite3_bind_int(stmt, 3, entity.getServiceType());

	rc = sqlite3_step(stmt);
	rc = sqlite3_reset(stmt);
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_finalize(stmt);
};

void ServiceRepository::remove(const Service& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::DELETE.c_str(), -1, &stmt, 0);
	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
	rc = sqlite3_bind_int64(stmt, 1, entity.getId());
	rc = sqlite3_step(stmt);
	checkSQLError(rc, zErrMsg);
	rc = sqlite3_reset(stmt);
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_finalize(stmt);
};

void ServiceRepository::update(const Service& entity) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);

	rc = sqlite3_bind_double(stmt, 1, entity.getCommission());
	rc = sqlite3_bind_int64(stmt, 2, entity.getId());

	rc = sqlite3_step(stmt);

	checkSQLError(rc, zErrMsg);
	rc = sqlite3_reset(stmt);
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);
	checkSQLError(rc, zErrMsg);
	rc = sqlite3_finalize(stmt);
};

std::vector<Service> ServiceRepository::getByType(const int type) {
	char* zErrMsg = 0;
	int rc = 0;
	sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

	rc = sqlite3_prepare_v2(DB_connection, ServiceTable::SELECT_BY_TYPE.c_str(), -1, &stmt, 0);

	rc = sqlite3_bind_int(stmt, 1, type);

	rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
	retrieveData();
	rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

	checkSQLError(rc, zErrMsg);

	rc = sqlite3_reset(stmt);
	rc = sqlite3_finalize(stmt);

	return data;
};