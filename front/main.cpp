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
    setlocale(LC_ALL,"Russian");
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/logo.png"));
    w.setWindowTitle("Payment terminal developed by Pershuta, Nakytniak, Levchuk");
    w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    w.show();
	a.exec();
	return 0;
}




