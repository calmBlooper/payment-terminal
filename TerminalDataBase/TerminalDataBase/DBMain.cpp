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

#include "DBManager.h"

int main(void)
{
	DBManager db;

	std::cout << "Private:" << std::endl;

	PrivateAccount pa1(Currency::UAH, 100.0,"Vadym","Nakytniak");
	PrivateAccount pa2(Currency::EUR, 999000.0, "Trokhym", "Babych");
	PrivateAccount pa3(Currency::UAH, 1000.0, "Alex", "Sad");
	PrivateAccount pa4(Currency::USD, 100000.0, "megakiller2005", "");
	db.getPrivateRepAcc().insert(pa1);
	db.getPrivateRepAcc().insert(pa2);
	db.getPrivateRepAcc().insert(pa3);
	db.getPrivateRepAcc().insert(pa4);

	db.getPrivateRepAcc().remove(db.getPrivateRepAcc().getByKey({ "megakiller2005", "" }));

	auto vn = db.getPrivateRepAcc().getByKey({ "Vadym", "Nakytniak"});
	std::cout << vn << std::endl;
	vn.replenish(888,Currency::UAH);
	db.getPrivateRepAcc().update(vn);

	PrivateAccount wrong(-100,Currency::UAH, 100.0, "d", "d");
	db.getPrivateRepAcc().update(wrong);
	db.getPrivateRepAcc().remove(wrong);
	
	auto res = db.getPrivateRepAcc().getAll();

	for (const auto acc : res)
	{
		std::cout << acc << std::endl;
	}

	auto acc = db.getPrivateRepAcc().getByKey({ "Vadym", "Nakytniak" });
	std::cout << acc << std::endl;

	std::cout << "Public:" << std::endl;

	PublicAccount pubAcc(Currency::USD, 100.0, "Apple.inc", "Silicon valley");
	db.getPublicRepAcc().insert(pubAcc);

	auto a1 = db.getPublicRepAcc().getByKey("Apple.inc");
	std::cout << a1 << std::endl;

	std::cout << "Mobile:" << std::endl;

	MobileAccount mobAcc(Currency::UAH, 100.0, "380-060-37-890");
	db.getMobileRepAcc().insert(mobAcc);

	auto a2 = db.getMobileRepAcc().getByKey("380-060-37-890");
	std::cout << a2 << std::endl;

	std::cout << "EWallet:" << std::endl;

	EWalletAccount ewallAcc(Currency::UAH, 100.0, "megakiller", "mgkkllr@ukma.edu.ua");
	db.getEWalletRepAcc().insert(ewallAcc);

	auto a3 = db.getEWalletRepAcc().getByKey("megakiller");
	std::cout << a3 << std::endl;

	return 0;
}