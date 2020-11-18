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

	db.getPrivateRepAcc().remove(db.getPrivateRepAcc().getByKey({ "megakiller2005", "" }));

	auto vn = db.getPrivateRepAcc().getByKey({ "Vadym", "Nakytniak" });
	std::cout << vn << std::endl;
	vn.replenish(888, Currency::UAH);
	db.getPrivateRepAcc().update(vn);

	std::cout << "By id:";

	auto vnid = db.getPrivateRepAcc().getById(vn.getId());
	std::cout << vnid << std::endl;

	PrivateAccount wrong(-100, Currency::UAH, 100.0, "d", "d");
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

	auto a1 = db.getPublicRepAcc().getByKey("Apple.inc");
	std::cout << a1 << std::endl;

	std::cout << "Mobile:" << std::endl;

	auto a2 = db.getMobileRepAcc().getByKey("380-060-37-890");
	std::cout << a2 << std::endl;

	std::cout << "EWallet:" << std::endl;

	auto byLogin = db.getEWalletRepAcc().getByLogin("megakiller");
	std::cout << byLogin << std::endl;

	auto byEmail = db.getEWalletRepAcc().getByEmail("mgkkllr@ukma.edu.ua");
	std::cout << byEmail << std::endl;

	auto byKey = db.getEWalletRepAcc().getByKey({ "megakiller", "mgkkllr@ukma.edu.ua" });
	std::cout << byKey << std::endl;

	std::cout << "Service Test:" << std::endl;
	auto s = db.getServiceRep().getByKey("Fortnite");
	std::cout << s << std::endl;

	auto ss = db.getServiceRep().getAll();
	for (auto x : ss) std::cout << x << std::endl;

	auto t0 = db.getServiceRep().getByType(0);
	for (auto x : t0) std::cout << x << std::endl;

	auto t1 = db.getServiceRep().getByType(1);
	for (auto x : t1) std::cout << x << std::endl;

	std::cout << "Paycard Test:" << std::endl;

	auto kk = db.getPaycardRep().getByKey("1010-2020-3030-4040");
	std::cout << kk << std::endl;

	auto kkk = db.getPaycardRep().getAll();
	for (auto x : kkk) std::cout << x << std::endl;


	std::cout << "By id:";

	auto tete = db.getPrivateRepAcc().getById(123);
	std::cout << tete << std::endl;

	return 0;
}