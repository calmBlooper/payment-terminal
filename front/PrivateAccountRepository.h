#pragma once

#include "PrivateAccount.h"
#include "Repository.h"

#include <string>
#include <utility>

#include "DBConnector.h"

class PrivateAccountRepository : public Repository<PrivateAccount, std::pair<std::string,std::string>> {
private:
    sqlite3_stmt* stmt = 0;
    std::vector<PrivateAccount> data;

    void retrieveData() {
        data.clear();
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            assert(sqlite3_column_count(stmt) == 5);

            const __int64 id = sqlite3_column_int64(stmt, 0);
            const std::string currency = std::string((const char*)sqlite3_column_text(stmt, 1));
            const double balance = sqlite3_column_double(stmt, 2);
            const std::string name = std::string((const char*)sqlite3_column_text(stmt, 3));
            const std::string surename = std::string((const char*)sqlite3_column_text(stmt, 4));

            data.push_back(PrivateAccount(id, currency, balance, name, surename));
        }
    }

public:
    PrivateAccountRepository()
    {
        return;
    };

    ~PrivateAccountRepository() {
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

    PrivateAccount getById(const __int64& id) {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::GET_BY_ID.c_str(), -1, &stmt, 0);

        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
        rc = sqlite3_bind_int(stmt, 1, id);
        retrieveData();
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

        checkSQLError(rc, zErrMsg);

        rc = sqlite3_reset(stmt);
        rc = sqlite3_finalize(stmt);

        return data.empty() ? PrivateAccount() : data.front();
    };

    virtual PrivateAccount getByKey(const std::pair<std::string, std::string>& nameSurename) {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());
        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::GET.c_str(), -1, &stmt, 0);

        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
        const char* name = nameSurename.first.c_str();
        const char* surename = nameSurename.second.c_str();
        rc = sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
        rc = sqlite3_bind_text(stmt, 2, surename, strlen(surename), SQLITE_STATIC);
        retrieveData();
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

        checkSQLError(rc, zErrMsg);

        rc = sqlite3_reset(stmt);
        rc = sqlite3_finalize(stmt);

        return data.empty() ? PrivateAccount(): data.front();
    };

    virtual std::vector<PrivateAccount> getAll() {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::SELECT.c_str(), -1, &stmt, 0);

        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
        retrieveData();
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

        checkSQLError(rc, zErrMsg);

        rc = sqlite3_reset(stmt);
        rc = sqlite3_finalize(stmt);

        return data;
    };
    virtual void insert(const PrivateAccount& entity) {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::INSERT.c_str(), -1, &stmt, 0);
        //  Optional, but will most likely increase performance.
        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
        //  Bind-parameter indexing is 1-based.
        rc = sqlite3_bind_text(stmt, 1, entity.getCurrency().c_str(), strlen(entity.getCurrency().c_str()), SQLITE_STATIC);
        rc = sqlite3_bind_double(stmt, 2, entity.getBalance());
        rc = sqlite3_bind_text(stmt, 3, entity.getName().c_str(), strlen(entity.getName().c_str()), SQLITE_STATIC);
        rc = sqlite3_bind_text(stmt, 4, entity.getSurename().c_str(), strlen(entity.getSurename().c_str()), SQLITE_STATIC);
        //  Step, Clear and Reset the statement after each bind.
        rc = sqlite3_step(stmt);
        rc = sqlite3_reset(stmt);
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg); //  End the transaction.

        checkSQLError(rc, zErrMsg);

        rc = sqlite3_finalize(stmt);  //  Finalize the prepared statement.
    };
    virtual void remove(const PrivateAccount& entity) {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::DELETE.c_str(), -1, &stmt, 0);
        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, 0);
        rc = sqlite3_bind_int64(stmt, 1, entity.getId());
        rc = sqlite3_step(stmt);
        checkSQLError(rc, zErrMsg);
        rc = sqlite3_reset(stmt);
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg);

        checkSQLError(rc, zErrMsg);

        rc = sqlite3_finalize(stmt);
    };
    virtual void update(const PrivateAccount& entity) {
        char* zErrMsg = 0;
        int rc = 0;
        sqlite3* DB_connection = (DBConnector::GetInstance()->getConnection());

        rc = sqlite3_prepare_v2(DB_connection, PrivateAccountTable::UPDATE_BY_ID.c_str(), -1, &stmt, 0);
        //  Optional, but will most likely increase performance.
        rc = sqlite3_exec(DB_connection, "BEGIN TRANSACTION", 0, 0, &zErrMsg);
        //  Bind-parameter indexing is 1-based.
        rc = sqlite3_bind_double(stmt, 1, entity.getBalance());
        rc = sqlite3_bind_int64(stmt, 2, entity.getId());
        //  Step, Clear and Reset the statement after each bind.
        rc = sqlite3_step(stmt);

        checkSQLError(rc, zErrMsg);
        rc = sqlite3_reset(stmt);
        rc = sqlite3_exec(DB_connection, "END TRANSACTION", 0, 0, &zErrMsg); //  End the transaction.
        checkSQLError(rc, zErrMsg);
        rc = sqlite3_finalize(stmt);  //  Finalize the prepared statement.
    };

};
