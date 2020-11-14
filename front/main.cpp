#include "mainwindow.h"
#include <QApplication>
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


int main(int argc, char* argv[])
{
	DBManager db;

	std::cout << "Private:" << std::endl;

	PrivateAccount pa1(Currency::UAH, 100.0, "Vadym", "Nakytniak");
	PrivateAccount pa2(Currency::EUR, 999000.0, "Trokhym", "Babych");
	PrivateAccount pa3(Currency::UAH, 1000.0, "Alex", "Sad");
	PrivateAccount pa4(Currency::USD, 100000.0, "megakiller2005", "");
	db.getPrivateRepAcc().insert(pa1);
	db.getPrivateRepAcc().insert(pa2);
	db.getPrivateRepAcc().insert(pa3);
	db.getPrivateRepAcc().insert(pa4);

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

	auto byLogin = db.getEWalletRepAcc().getByLogin("megakiller");
	std::cout << byLogin << std::endl;

	auto byEmail = db.getEWalletRepAcc().getByEmail("mgkkllr@ukma.edu.ua");
	std::cout << byEmail << std::endl;

	auto byKey = db.getEWalletRepAcc().getByKey({ "megakiller", "mgkkllr@ukma.edu.ua" });
	std::cout << byKey << std::endl;

	std::cout << "Service Test:" << std::endl;

	Service serv01(0, "Fortnite", .30);
	Service serv02(0, "Dota 2", .10);
	Service serv11(1, "Steam", .20);
	Service serv12(1, "EpicStore", .20);
	db.getServiceRep().insert(serv01);
	db.getServiceRep().insert(serv02);
	db.getServiceRep().insert(serv11);
	db.getServiceRep().insert(serv12);

	auto s = db.getServiceRep().getByKey("Fortnite");
	std::cout << s << std::endl;

	auto ss = db.getServiceRep().getAll();
	for (auto x : ss) std::cout << x << std::endl;

	auto t0 = db.getServiceRep().getByType(0);
	for (auto x : t0) std::cout << x << std::endl;

	auto t1 = db.getServiceRep().getByType(1);
	for (auto x : t1) std::cout << x << std::endl;

	std::cout << "Paycard Test:" << std::endl;

	Paycard pc(vn.getId(), "1010-2020-3030-4040", 123, 12, 2077, 4040);
	Paycard pc2(vn.getId(), "777", 777, 777, 777, 777);

	db.getPaycardRep().insert(pc);
	db.getPaycardRep().insert(pc2);

	auto kk = db.getPaycardRep().getByKey("1010-2020-3030-4040");
	std::cout << kk << std::endl;

	auto kkk = db.getPaycardRep().getAll();
	for (auto x : kkk) std::cout << x << std::endl;
  QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/logo.png"));
    w.setWindowTitle("Payment terminal developed by Pershuta, Nakytniak, Levchuk");
    w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    w.show();
	a.exec();
	return 0;
}




