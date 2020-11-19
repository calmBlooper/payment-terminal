#pragma once

#include <iostream>

#include "DBConnector.h"

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

	void checkSQLError(const int rc, char* zErrMsg);

	void createTables();
	void fillUpTheTables();
	void initDb();

public:
	DBManager(const bool& shouldInit = false);
	~DBManager();

	PrivateAccountRepository& getPrivateRepAcc();
	PublicAccountRepository& getPublicRepAcc();
	MobileAccountRepository& getMobileRepAcc();
	EWalletAccountRepository& getEWalletRepAcc();
	ServiceRepository& getServiceRep();
	PaycardRepository& getPaycardRep();

};