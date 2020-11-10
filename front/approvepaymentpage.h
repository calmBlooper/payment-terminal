#ifndef APPROVEPAYMENTPAGE_H
#define APPROVEPAYMENTPAGE_H

#include <QDialog>

namespace Ui {
class ApprovePaymentPage;
}

class ApprovePaymentPage : public QDialog
{
    Q_OBJECT

public:
    explicit ApprovePaymentPage(QString account = "",QString card = "",QString sum = "", QString year = "",QString month = "",QString cvv2 = "", QWidget *parent = nullptr);
    ~ApprovePaymentPage();

    const QString& getEnteredPin();
private slots:

    void on_num_1_clicked();
    void on_num_2_clicked();
    void on_num_3_clicked();
    void on_num_4_clicked();
    void on_num_5_clicked();
    void on_num_6_clicked();
    void on_num_7_clicked();
    void on_num_8_clicked();
    void on_num_9_clicked();
    void on_num_0_clicked();
    void on_cl_one_clicked();
    void on_cl_all_clicked();

    void on_accept_clicked();

    void on_pin_field_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ApprovePaymentPage *ui;
    QString account;
    QString cardNumber;
    QString sum;
    QString year;
    QString month;
    QString cvv2;

    static int tries;
};

#endif // APPROVEPAYMENTPAGE_H
