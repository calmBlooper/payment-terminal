#pragma once

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

#include "PrivateAccountRepository.h"
#include "PublicAccountRepository.h"
#include "MobileAccountRepository.h"
#include "EWalletAccountRepository.h"
#include "ServiceRepository.h"
#include "PaycardRepository.h"

class DBManager {
private:
	PrivateAccountRepository privateRep;
	PublicAccountRepository publicRep;
	MobileAccountRepository mobileRep;
	EWalletAccountRepository ewalletRep;

	ServiceRepository serviceRep;
	PaycardRepository paycardRep;

	const char* dir = "test.db";

	void checkSQLError(const int rc, char* zErrMsg) {
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Table not created. SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Table created successfully\n");
		}
	}

	void createTables() {
		char* zErrMsg = 0;
		int rc = 0;
		auto connection = DBConnector::GetInstance()->getConnection();
		rc = sqlite3_exec(connection, PrivateAccountTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_exec(connection, PublicAccountTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_exec(connection, MobileAccountTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_exec(connection, EWalletAccountTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_exec(connection, PaycardTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
		rc = sqlite3_exec(connection, ServiceTable::CREATE_TABLE.c_str(), 0, 0, &zErrMsg);
		checkSQLError(rc, zErrMsg);
	}

	void fillUpTheTables() {
		PrivateAccount pa1(Currency::UAH, 100.0, "Vadym", "Nakytniak");
		PrivateAccount pa2(Currency::EUR, 999000.0, "Trokhym", "Babych");
		PrivateAccount pa3(Currency::UAH, 1000.0, "Alex", "Sad");
		PrivateAccount pa4(Currency::USD, 100000.0, "megakiller2005", "");
		privateRep.insert(pa1);
		privateRep.insert(pa2);
		privateRep.insert(pa3);
		privateRep.insert(pa4);

		PublicAccount pubAcc(Currency::USD, 100.0, "Apple.inc", "Silicon valley");
		publicRep.insert(pubAcc);

		MobileAccount mobAcc(Currency::UAH, 100.0, "380-060-37-890");
		mobileRep.insert(mobAcc);

		EWalletAccount ewallAcc(Currency::UAH, 100.0, "megakiller", "mgkkllr@ukma.edu.ua");
		ewalletRep.insert(ewallAcc);


		Paycard pc(pa1.getId(), "1010-2020-3030-4040", 123, 12, 2077, 4040);
		Paycard pc2(pa1.getId(), "777", 777, 777, 777, 777);

		paycardRep.insert(pc);
		paycardRep.insert(pc2);

		Service serv01(0, "Fortnite", .30);
		Service serv02(0, "Dota 2", .10);
		Service serv11(1, "Steam", .20);
		Service serv12(1, "EpicStore", .20);
		serviceRep.insert(serv01);
		serviceRep.insert(serv02);
		serviceRep.insert(serv11);
		serviceRep.insert(serv12);
	}

	void initDb() {
		createTables();
		fillUpTheTables();
	}

public:
	DBManager(const bool& shouldInit = false) {
		DBConnector::InitConnection(dir)->getConnection();
		if (shouldInit)initDb();
	}
	~DBManager() {
		DBConnector::InitConnection(dir)->closeConnection();
	}

	PrivateAccountRepository& getPrivateRepAcc() {
		return privateRep;
	}

	PublicAccountRepository& getPublicRepAcc() {
		return publicRep;
	}

	MobileAccountRepository& getMobileRepAcc() {
		return mobileRep;
	}

	EWalletAccountRepository& getEWalletRepAcc() {
		return ewalletRep;
	}

	ServiceRepository& getServiceRep() {
		return serviceRep;
	}

	PaycardRepository& getPaycardRep() {
		return paycardRep;
	}

};