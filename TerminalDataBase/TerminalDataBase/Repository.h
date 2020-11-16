#pragma once

#include<vector>

#include "Identifiable.h"

template <class T, class K>
class Repository
{
private:
protected:
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
public:
    virtual ~Repository() {
        return;
    };
    virtual T getByKey(const K& key) = 0;
    virtual std::vector<T> getAll() = 0;
    virtual void insert(const T& entity) = 0;
    virtual void remove(const T& entity) = 0;
    virtual void update(const T& entity) = 0;
};