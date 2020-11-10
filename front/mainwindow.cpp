#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include<stdio.h>
int MainWindow::digitsInPhoneNumber = 20;
int MainWindow::service = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp cardRegex ("(\\d{4}[-. ]?){4}|\\d{4}[-. ]?\\d{6}[-. ]?\\d{5}");
    QRegExp monthRegex ("01|02|03|04|05|06|07|08|09|10|11|12");
    QRegExp yearRegex ("^[2-9][0-9]");
    QRegExp cvvRegex ("[0-9]{3}");
    QRegExp sumRegex ("\\d{1,5}|100000");
    QRegExpValidator *cardValidator = new QRegExpValidator(cardRegex, this);
    ui->card_number->setValidator(cardValidator);
    QRegExpValidator *monthValidator = new QRegExpValidator(monthRegex, this);
    ui->month_field->setValidator(monthValidator);
    QRegExpValidator *yearValidator = new QRegExpValidator(yearRegex, this);
    ui->year_field->setValidator(yearValidator);
    QRegExpValidator *cvvValidator = new QRegExpValidator(cvvRegex, this);
    ui->cvv2_field->setValidator(cvvValidator);
    QRegExpValidator *sumValidator = new QRegExpValidator(sumRegex, this);
    ui->label_trans_sum->setValidator(sumValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_steam_button_clicked()
{

}
void MainWindow::clearFields(){
    ui->label_phone_number->setText("");
    ui->is_transfer_beznal->setChecked(false);
    ui->label_trans_sum->setText("");
    ui->label_phone_number->setPlaceholderText("");
    ui->actual_cash_entered_label->setText("0");
    ui->actual_cash_bez_com->setText("0");
    ui->label_phone_number->setStyleSheet("background-color: rgb(255, 255, 255);"
                                          " border-width: 3px;"
                                          " border-radius: 10px;"
                                          " border-color:  #331E38;"
                                          " border-style:solid;"
                                          " outline: 0;");
    ui->confirm_nal_payment->setHidden(true);
    ui->cancel_payment_button->setHidden(false);
}
void MainWindow::on_mob_button_clicked()
{
   ui->label_account_9->setText("Введіть номер телефону:");
   ui->stackedWidget->setCurrentIndex(1);
   QRegExp phoneRegex ("^\\s*(?:\\+?(\\d{1,3}))?([-. (]*(\\d{3})[-. )]*)?((\\d{3})[-. ]*(\\d{2,4})(?:[-.x ]*(\\d+))?)\\s*$");
   QRegExpValidator *phoneValidator = new QRegExpValidator(phoneRegex, this);
   ui->label_phone_number->setValidator(phoneValidator);
}

void MainWindow::on_cancel_button_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);
    clearFields();
}

void MainWindow::addTextToAccountField(QString str){
    QString text = ui->label_phone_number->text();
    if(text.length()<digitsInPhoneNumber)
        ui->label_phone_number->setText(text+str);
}

void MainWindow::on_num_1_account_clicked()
{
   addTextToAccountField("1");
}
void MainWindow::on_num_2_account_clicked()
{
     addTextToAccountField("2");
}
void MainWindow::on_num_3_account_clicked()
{
      addTextToAccountField("3");
}
void MainWindow::on_num_4_account_clicked()
{
      addTextToAccountField("4");
}
void MainWindow::on_num_5_account_clicked()
{
      addTextToAccountField("5");
}
void MainWindow::on_num_6_account_clicked()
{
     addTextToAccountField("6");
}
void MainWindow::on_num_7_account_clicked()
{
     addTextToAccountField("7");
}
void MainWindow::on_num_8_account_clicked()
{
    addTextToAccountField("8");
}
void MainWindow::on_num_9_account_clicked()
{
    addTextToAccountField("9");
}
void MainWindow::on_num_0_account_clicked()
{
     addTextToAccountField("0");
}
void MainWindow::on_cl_one_account_clicked()
{
    ui->label_phone_number->backspace();
}
void MainWindow::on_cl_all_account_clicked()
{
     ui->label_phone_number->setText("");
}

void MainWindow::on_go_to_payment_page_clicked()
{
    if(ui->label_phone_number->text().length()==0){
        ui->label_phone_number->setPlaceholderText("Введіть номер рахунку");
        ui->label_phone_number->setStyleSheet("background-color: rgb(255, 255, 255);"
                                              " border-width: 5px;"
                                              " border-radius: 10px;"
                                              " border-color:  red;"
                                              " border-style:solid;"
                                              " outline: 0;");
    }
    else{
        ui->label_phone_number->setPlaceholderText("");
        ui->label_phone_number->setStyleSheet("background-color: rgb(255, 255, 255);"
                                              " border-width: 3px;"
                                              " border-radius: 10px;"
                                              " border-color:  #331E38;"
                                              " border-style:solid;"
                                              " outline: 0;");

        if(ui->is_transfer_beznal->isChecked())
            ui->stackedWidget->setCurrentIndex(3);
        else{
            ui->confirm_nal_payment->setHidden(true);
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void MainWindow::on_cancel_sum_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearFields();
}

void MainWindow::on_cancel_payment_button_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     clearFields();
}
void MainWindow::validateSumOfTransfer(QString str){
    if( ui->label_trans_sum->text().length()<5 ||
            (ui->label_trans_sum->text().endsWith("10000")&& str.endsWith("0")))
         ui->label_trans_sum->setText(ui->label_trans_sum->text()+str);
}
void MainWindow::on_num_1_transfer_clicked()
{
    validateSumOfTransfer("1");
}
void MainWindow::on_num_2_transfer_clicked()
{
     validateSumOfTransfer("2");
}
void MainWindow::on_num_3_transfer_clicked()
{
    validateSumOfTransfer("3");
}
void MainWindow::on_num_4_transfer_clicked()
{
     validateSumOfTransfer("4");
}
void MainWindow::on_num_5_transfer_clicked()
{
    validateSumOfTransfer("5");
}
void MainWindow::on_num_6_transfer_clicked()
{
     validateSumOfTransfer("6");
}
void MainWindow::on_num_7_transfer_clicked()
{
    validateSumOfTransfer("7");
}
void MainWindow::on_num_8_transfer_clicked()
{
     validateSumOfTransfer("8");
}
void MainWindow::on_num_9_transfer_clicked()
{
     validateSumOfTransfer("9");
}
void MainWindow::on_num_0_transfer_clicked()
{
     validateSumOfTransfer("0");
}
void MainWindow::on_cl_one_transfer_clicked()
{
    ui->label_trans_sum->backspace();
}
void MainWindow::on_cl_all_transfer_clicked()
{
     ui->label_trans_sum->setText("");
}


void MainWindow::on_goto_card_inf_clicked()
{

     if(ui->label_trans_sum->text().length()==0){
         ui->label_trans_sum->setPlaceholderText("Введіть суму переказу");
         ui->label_trans_sum->setStyleSheet("background-color: rgb(255, 255, 255);"
                                               " border-width: 5px;"
                                               " border-radius: 10px;"
                                               " border-color:  red;"
                                               " border-style:solid;"
                                               " outline: 0;");
     }
     else{
         ui->label_trans_sum->setPlaceholderText("");
         ui->label_trans_sum->setStyleSheet("background-color: rgb(255, 255, 255);"
                                               " border-width: 3px;"
                                               " border-radius: 10px;"
                                               " border-color:  #331E38;"
                                               " border-style:solid;"
                                               " outline: 0;");
          ui->stackedWidget->setCurrentIndex(4);
}
}

void MainWindow::on_cancel_button_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->card_number->setText("");
    ui->month_field->setText("");
    ui->year_field->setText("");
    ui->cvv2_field->setText("");
    clearFields();
}
double countCommision(int uan, int service){
    switch(service){
    case 0:
        return uan*0.03 > 50 ? 50: uan*0.03;
    case 1:
        return uan*0.05 > 200 ? 200: uan*0.05;
    }
    return 0;
}
void MainWindow::addCash(int uan, int service)
{
  ui->cancel_payment_button->setHidden(true);
  ui->confirm_nal_payment->setHidden(false);
  QString entered = ui->actual_cash_entered_label->text();
  int val1 = entered.toInt()+uan;
   if(val1>100000)
       return;
  ui->actual_cash_entered_label->setText(QString::number(val1));
  ui->actual_cash_bez_com->setText(QString::number(val1-countCommision(val1, service)));

}
void MainWindow::on_uan5_button_clicked()
{
     addCash(5,service);
}

void MainWindow::on_uan10_button_clicked()
{
    addCash(10,service);
}

void MainWindow::on_uan20_button_clicked()
{
     addCash(20,service);
}

void MainWindow::on_uan50_button_clicked()
{
    addCash(50,service);
}

void MainWindow::on_uan100_button_clicked()
{
    addCash(100,service);
}

void MainWindow::on_uan200_button_clicked()
{
    addCash(200,service);
}

void MainWindow::on_uan500_button_clicked()
{
    addCash(500,service);
}

void MainWindow::on_uan1000_button_clicked()
{
    addCash(1000,service);
}

QString replaceAll(QString str){
    for(int i = 0; i< str.length(); i++){
        if(str.at(i) == ' ')
            str.replace(i,1,"");
    }
    return str;
}

void MainWindow::addCardData(QString data)
{
  if( ui->f1_button->isChecked()&&replaceAll(ui->card_number->text()).length()<16){
     ui->card_number->setText(ui->card_number->text()+data);
  }
  if( ui->f2->isChecked()){
    if(ui->month_field->text().length()<2)
        ui->month_field->setText(ui->month_field->text()+data);
    else
       ui->year_field->setText(ui->year_field->text()+data);
  }
  if( ui->f3->isChecked()){
     ui->cvv2_field->setText(ui->cvv2_field->text()+data);
  }
}


void MainWindow::on_f1_clicked()
{
    ui->f1_button->setChecked(true);
    ui->f2->setChecked(false);
    ui->f3->setChecked(false);
}

void MainWindow::on_f2_clicked()
{
    ui->f1_button->setChecked(false);
    ui->f2->setChecked(true);
    ui->f3->setChecked(false);
}

void MainWindow::on_f3_clicked()
{
    ui->f1_button->setChecked(false);
    ui->f2->setChecked(false);
    ui->f3->setChecked(true);
}

void MainWindow::on_num_1_data_clicked()
{
    addCardData("1");
}

void MainWindow::on_num_2_data_clicked()
{
    addCardData("2");
}

void MainWindow::on_num_3_data_clicked()
{
    addCardData("3");
}
void MainWindow::on_num_4_data_clicked()
{
    addCardData("4");
}
void MainWindow::on_num_5_data_clicked()
{
    addCardData("5");
}
void MainWindow::on_num_6_data_clicked()
{
    addCardData("6");
}
void MainWindow::on_num_7_data_clicked()
{
    addCardData("7");
}
void MainWindow::on_num_8_data_clicked()
{
    addCardData("8");
}
void MainWindow::on_num_9_data_clicked()
{
    addCardData("9");
}
void MainWindow::on_num_0_data_clicked()
{
    addCardData("0");
}

void MainWindow::on_cl_one_data_clicked()
{
    if( ui->f1_button->isChecked()){
        ui->card_number->backspace();
    }
    if( ui->f2->isChecked()){
        if(ui->year_field->text().length()>0)
            ui->year_field->backspace();
        else if(ui->month_field->text().length()>0)
            ui->month_field->backspace();
    }
    if( ui->f3->isChecked()){
         ui->cvv2_field->backspace();
    }
}

void MainWindow::on_cl_all_data_clicked()
{
    if( ui->f1_button->isChecked()){
        ui->card_number->clear();
    }
    if( ui->f2->isChecked()){
        ui->year_field->clear();
        ui->month_field->clear();
    }
    if( ui->f3->isChecked()){
        ui->cvv2_field->clear();
    }
}

void MainWindow::on_goto_transfer_details_clicked()
{
    QRegExp cardRegex ("(\\d{4}[-. ]?){4}|\\d{4}[-. ]?\\d{6}[-. ]?\\d{5}");
    QRegExp monthRegex ("01|02|03|04|05|06|07|08|09|10|11|12");
    QRegExp yearRegex ("^[2-9][0-9]");
    QRegExp cvvRegex ("[0-9]{3}");
    if(!cardRegex.exactMatch(ui->card_number->text()))
    {
        ui->card_number->setStyleSheet("background-color: rgb(255, 255, 255);"
                                       " border-width: 5px;"
                                       " border-radius: 10px;"
                                       " border-color:  red;"
                                       " border-style:solid;"
                                       " outline: 0;");
    }
    else if(!monthRegex.exactMatch(ui->month_field->text()))
    {
        ui->month_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                       " border-width: 5px;"
                                       " border-radius: 10px;"
                                       " border-color:  red;"
                                       " border-style:solid;"
                                       " outline: 0;");
    }
    else if(!yearRegex.exactMatch(ui->year_field->text()))
    {
        ui->year_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                       " border-width: 5px;"
                                       " border-radius: 10px;"
                                       " border-color:  red;"
                                       " border-style:solid;"
                                       " outline: 0;");
    }
    else if(!cvvRegex.exactMatch(ui->cvv2_field->text()))
    {
        ui->cvv2_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                       " border-width: 5px;"
                                       " border-radius: 10px;"
                                       " border-color:  red;"
                                       " border-style:solid;"
                                       " outline: 0;");
    }
    else{
        double com = ui->label_trans_sum->text().toInt() + countCommision(ui->label_trans_sum->text().toInt(), MainWindow::service);
        ui->account_data->setText("Номер рахунку: " +  ui->label_phone_number->text());
        ui->card_data->setText("Номер карти: " +  ui->card_number->text());
        ui->to_pay_data->setText("До сплати: " + QString::number(com));
        ui->stackedWidget->setCurrentIndex(5);
    }
}


void MainWindow::on_card_number_textChanged(const QString &)
{
    ui->card_number->setStyleSheet("background-color: rgb(255, 255, 255);"
                                          " border-width: 3px;"
                                          " border-radius: 10px;"
                                          " border-color:  #331E38;"
                                          " border-style:solid;"
                                          " outline: 0;");
}

void MainWindow::on_month_field_textChanged(const QString &)
{
    ui->month_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                          " border-width: 3px;"
                                          " border-radius: 10px;"
                                          " border-color:  #331E38;"
                                          " border-style:solid;"
                                          " outline: 0;");
}

void MainWindow::on_year_field_textChanged(const QString &)
{
    ui->year_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                          " border-width: 3px;"
                                          " border-radius: 10px;"
                                          " border-color:  #331E38;"
                                          " border-style:solid;"
                                          " outline: 0;");
}

void MainWindow::on_cvv2_field_textChanged(const QString &)
{
    ui->cvv2_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                          " border-width: 3px;"
                                          " border-radius: 10px;"
                                          " border-color:  #331E38;"
                                          " border-style:solid;"
                                          " outline: 0;");
}

void MainWindow::on_confirm_payment_clicked()
{
    ApprovePaymentPage approvementPage(ui->label_phone_number->text(),ui->card_number->text(),ui->label_trans_sum->text(),ui->year_field->text(),ui->month_field->text(),ui->cvv2_field->text());
    approvementPage.setModal(true);
    approvementPage.exec();
    if(approvementPage.result()==1){
        ui->check->setText("Номер рахунку: " +ui->label_phone_number->text() + '\n'+
                          "Номер карти: " +ui->card_number->text() + '\n'+
                          "Сума платежу: " +ui->label_trans_sum->text() + '\n'+
                          "Сума комісії: " +QString::number(countCommision(ui->label_trans_sum->text().toInt(), MainWindow::service)));
        ui->stackedWidget->setCurrentIndex(6);

    }
    if(approvementPage.result()==0){
         ui->stackedWidget->setCurrentIndex(7);
    }
}

void MainWindow::on_back_to_main_menu_clicked()
{
    clearFields();
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    clearFields();
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_confirm_nal_payment_clicked()
{
    QString acc = ui->label_phone_number->text();
    QString sum = ui->actual_cash_entered_label->text();
    double com = countCommision(sum.toDouble(), MainWindow::service);
    // send payment request
    //
    bool success = true;
    if(success){
        ui->check->setText("Номер рахунку: " +acc + '\n'+
                          "Внесено готівки: " +sum + '\n'+
                          "Сума комісії: " +QString::number(com) + '\n');
        ui->stackedWidget->setCurrentIndex(6);
    }
    else{
         ui->stackedWidget->setCurrentIndex(7);
    }

}
