
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_steam_button_clicked();
    void on_mob_button_clicked();
    void on_cancel_button_clicked();
    void on_num_1_account_clicked();
    void on_num_2_account_clicked();
    void on_num_3_account_clicked();
    void on_num_4_account_clicked();
    void on_num_5_account_clicked();
    void on_num_6_account_clicked();
    void on_num_7_account_clicked();
    void on_num_8_account_clicked();
    void on_num_9_account_clicked();
    void on_num_0_account_clicked();
    void on_cl_one_account_clicked();
    void on_cl_all_account_clicked();
    void on_go_to_payment_page_clicked();
    void on_cancel_sum_button_clicked();
    void on_cancel_payment_button_clicked();
    void validateSumOfTransfer(QString str);

    void on_num_1_transfer_clicked();
    void on_num_2_transfer_clicked();
    void on_num_3_transfer_clicked();
    void on_num_4_transfer_clicked();
    void on_num_5_transfer_clicked();
    void on_num_6_transfer_clicked();
    void on_num_7_transfer_clicked();
    void on_num_8_transfer_clicked();
    void on_num_9_transfer_clicked();
    void on_num_0_transfer_clicked();

    void on_cl_one_transfer_clicked();
    void on_cl_all_transfer_clicked();
    void on_goto_card_inf_clicked();
    void on_cancel_button_16_clicked();

    void on_uan5_button_clicked();
    void on_uan10_button_clicked();
    void on_uan20_button_clicked();
    void on_uan50_button_clicked();
    void on_uan100_button_clicked();
    void on_uan200_button_clicked();
    void on_uan500_button_clicked();
    void on_uan1000_button_clicked();



private:
    Ui::MainWindow *ui;
   static int digitsInPhoneNumber;
   static int service;
   void clearFields();
   void addTextToAccountField(QString str);
   void addCash(int uan, int service);
};
#endif // MAINWINDOW_H
