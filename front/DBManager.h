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
		PrivateAccount pa1(111, Currency::UAH(), 100.0, "Біба", "Боба");
		PrivateAccount pa2(222, Currency::UAH(), 999000.0, "Микола", "Шевчук");
		PrivateAccount pa3(333, Currency::UAH(), 1000.0, "Alex", "Sad");
		PrivateAccount pa4(444, Currency::UAH(), 100000.0, "Андрій", "Степаненко");
		privateRep.insert(pa1);
		privateRep.insert(pa2);
		privateRep.insert(pa3);
		privateRep.insert(pa4);

		PublicAccount pubAcc1(Currency::UAH(), 100.0, "Чоклинський Артем Вікторович", "вулиця Марини Цвєтаєвої, 14Б");
		publicRep.insert(pubAcc1);

		PublicAccount pubAcc2(Currency::USD(), 5360.64, "Михайлишин Павло Васильович", "вулиця Харківське шосе, 168є, кв. 325");
		publicRep.insert(pubAcc2);

		PublicAccount pubAcc3(Currency::USD(), 55.74, "Гігантюк Кіндрат Каленикович", "вулиця Зарічна, 1А, кв. 14");
		publicRep.insert(pubAcc3);

		MobileAccount mobAcc1(Currency::UAH(), 100.0, "380-060-37-890");
		mobileRep.insert(mobAcc1);

		MobileAccount mobAcc2(Currency::UAH(), 37.0, "380964334089");
		mobileRep.insert(mobAcc2);

		MobileAccount mobAcc3(Currency::UAH(), 10.0, "38006037890");
		mobileRep.insert(mobAcc3);

		EWalletAccount ewallAcc(Currency::UAH(), 100.0, "megakiller", "mgkkllr@ukma.edu.ua");
		ewalletRep.insert(ewallAcc);

		EWalletAccount ewallAcc1(Currency::UAH(), 400.0, "xxxTBaggerxxx", "usuck@hotmail.com");
		ewalletRep.insert(ewallAcc1);

		EWalletAccount ewallAcc2(Currency::UAH(), 420.0, "ChiziDorito", "potato69@gmail.com");
		ewalletRep.insert(ewallAcc2);

		Paycard pc1(pa1.getId(), "1010202030304040", 123, 12, 2027, 4040);
		Paycard pc2(pa2.getId(), "1234123412341234", 111, 1, 2025, 1111);
		Paycard pc3(pa1.getId(), "8673957495848765", 777, 10, 2025, 7537);
		Paycard pc4(pa2.getId(), "0975344495848765", 646, 11, 2024, 7537);
		Paycard pc5(pa2.getId(), "8673654355848765", 646, 5, 2027, 6426);
		Paycard pc6(pa3.getId(), "4645324495848765", 243, 6, 2028, 7537);
		Paycard pc7(pa3.getId(), "4545454545454545", 777, 7, 2025, 7537);
		Paycard pc8(pa3.getId(), "1948574937584957", 425, 8, 2029, 1111);
		Paycard pc9(pa4.getId(), "8573859485746375", 777, 9, 2025, 0000);
		Paycard pc10(pa4.getId(), "4673947495548765", 534, 1, 2023, 9743);
		paycardRep.insert(pc1);
		paycardRep.insert(pc2);
		paycardRep.insert(pc3);
		paycardRep.insert(pc4);
		paycardRep.insert(pc5);
		paycardRep.insert(pc6);
		paycardRep.insert(pc7);
		paycardRep.insert(pc8);
		paycardRep.insert(pc9);
		paycardRep.insert(pc10);
		Service serv01(0, "Київстар", .03);
		Service serv02(0, "lifecell (Life)", .03);
		Service serv03(0, "Vodafone ", .03);
		Service serv11(1, "ПриватБанк", .01);
		Service serv12(1, "WebMoney", .03);
		Service serv13(1, "PayPal", .02);
		Service serv21(2, "Цифрал сервіс", 0.0);
		Service serv22(2, "Київводоканал", .02);
		Service serv31(3, "STAR WARS™: The Old Republic™", .14);
		Service serv32(3, "Warthunder", .15);
		Service serv33(3, "Поповнення гаманця Steam", .07);
		Service serv34(3, "GTA Online Shark Cards", .14);
		Service serv41(4, "Українська Біржа Благодійності", .02);
		Service serv42(4, "Червоний хрест", .02);
		Service serv43(4, "Всесвітній Центр Свідків Єгови", .02);
		serviceRep.insert(serv01);
		serviceRep.insert(serv02);
		serviceRep.insert(serv03);
		serviceRep.insert(serv11);
		serviceRep.insert(serv12);
		serviceRep.insert(serv13);
		serviceRep.insert(serv21);
		serviceRep.insert(serv22);
		serviceRep.insert(serv31);
		serviceRep.insert(serv32);
		serviceRep.insert(serv33);
		serviceRep.insert(serv34);
		serviceRep.insert(serv41);
		serviceRep.insert(serv42);
		serviceRep.insert(serv43);

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