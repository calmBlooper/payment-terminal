
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "approvepaymentpage.h"
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



    void on_num_1_data_clicked();

    void on_f1_clicked();

    void on_f2_clicked();

    void on_f3_clicked();

    void on_num_2_data_clicked();

    void on_num_3_data_clicked();
    void on_num_4_data_clicked();
    void on_num_5_data_clicked();
    void on_num_6_data_clicked();
    void on_num_7_data_clicked();
    void on_num_8_data_clicked();
    void on_num_9_data_clicked();
    void on_num_0_data_clicked();

    void on_cl_one_data_clicked();

    void on_cl_all_data_clicked();

    void on_goto_transfer_details_clicked();

    void on_card_number_textChanged(const QString &arg1);

    void on_month_field_textChanged(const QString &arg1);

    void on_year_field_textChanged(const QString &arg1);

    void on_cvv2_field_textChanged(const QString &arg1);


    void on_confirm_payment_clicked();

    void on_back_to_main_menu_clicked();

    void on_pushButton_2_clicked();

    void on_confirm_nal_payment_clicked();

private:
    Ui::MainWindow *ui;
   static int digitsInPhoneNumber;
   static int service;
   void clearFields();
   void addTextToAccountField(QString str);
   void addCash(int uan, int service);
   void addCardData(QString);
};
#endif // MAINWINDOW_H
