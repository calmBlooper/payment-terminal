#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/logo.png"));
    w.setWindowTitle("Payment terminal developed by Pershuta, Nakytniak, Levchuk");
    w.show();
    return a.exec();
}
