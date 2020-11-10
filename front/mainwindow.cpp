#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include<stdio.h>
#include "Utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->card_number->setValidator(new QRegExpValidator(Utils::cardNumberRegex, this));
    ui->month_field->setValidator(new QRegExpValidator(Utils::monthRegex, this));
    ui->year_field->setValidator(new QRegExpValidator(Utils::yearRegex, this));
    ui->cvv2_field->setValidator(new QRegExpValidator(Utils::cvv2Regex, this));
    ui->label_trans_sum->setValidator(new QRegExpValidator(Utils::sumOfTransferRegex, this));
    ui->pin_field->setValidator(new QRegExpValidator(Utils::pinRegex, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearFields(){
    ui->account_number->setText("");
    ui->is_transfer_beznal->setChecked(false);
    ui->label_trans_sum->setText("");
    ui->account_number->setPlaceholderText("");
    ui->actual_cash_entered_label->setText("0");
    ui->actual_cash_bez_com->setText("0");
    ui->account_number->setStyleSheet(Utils::style_usual);
    ui->confirm_nal_payment->setHidden(true);
    ui->cancel_payment_button->setHidden(false);
    ui->card_number->setText("");
    ui->month_field->setText("");
    ui->year_field->setText("");
    ui->cvv2_field->setText("");
    ui->pin_field->clear();
    ui->label_account_9->setFixedWidth(250);
    QFont font;
    font.setPointSize(15);
    ui->label_account_9->setFont(font);
}
QString replaceAll(QString str){
    for(int i = 0; i< str.length(); i++){
        if(str.at(i) == ' '||str.at(i) == '('||str.at(i) == ')')
            str.replace(i,1,"");
    }
    return str;
}

void MainWindow::on_cancel_button_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);
    clearFields();
}

void MainWindow::addTextToAccountField(QString str){
    QString text = replaceAll(ui->account_number->text());
    if(text.length()<=Utils::maxNumberOfDigits)
        ui->account_number->setText(ui->account_number->text()+str);
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
    ui->account_number->backspace();
}
void MainWindow::on_cl_all_account_clicked()
{
    ui->account_number->clear();
}

void MainWindow::on_go_to_payment_page_clicked()
{
    if(ui->account_number->text().length()==0){
        ui->account_number->setPlaceholderText("Введіть номер рахунку");
        ui->account_number->setStyleSheet(Utils::style_error);
    }
    else{
        ui->account_number->setPlaceholderText("");
        ui->account_number->setStyleSheet(Utils::style_usual);

        if(ui->is_transfer_beznal->isChecked()){
            ui->f1_button->setChecked(true);
            ui->stackedWidget->setCurrentIndex(3);
        }
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
    QString temp = ui->label_trans_sum->text()+str;
    if(Utils::sumOfTransferRegex.exactMatch(temp))
         ui->label_trans_sum->setText(temp);
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
     ui->label_trans_sum->clear();
}

double countCommision(int uan, int service){
    switch(service){
    case 0:case 2:
        return uan*0.03 > 50 ? 50: uan*0.03;
    case 1:
        return uan*0.05 > 200 ? 200: uan*0.05;
    case 3:
        return uan*0.07 > 500 ? 500: uan*0.07;
    }
    return 0;
}
void MainWindow::on_goto_pin_clicked()
{

     if(ui->label_trans_sum->text().length()==0){
         ui->label_trans_sum->setPlaceholderText("Введіть суму переказу");
         ui->label_trans_sum->setStyleSheet(Utils::style_error);
     }
     else{
         ui->label_trans_sum->setPlaceholderText("");
         ui->label_trans_sum->setStyleSheet(Utils::style_usual);
         double com = ui->label_trans_sum->text().toInt() + countCommision(ui->label_trans_sum->text().toInt(), Utils::service);
         ui->account_data->setText("Номер рахунку: " +  ui->account_number->text());
         ui->to_pay_sum->setText("Cума переказу: " +ui->label_trans_sum->text()+ " грн" );
         ui->card_data->setText("Номер карти: " +  ui->card_number->text());
         ui->to_pay_data->setText("До сплати: " + QString::number(com)+ " грн");
         ui->stackedWidget->setCurrentIndex(5);
}
}

void MainWindow::on_cancel_button_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearFields();
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
     addCash(5,Utils::service);
}

void MainWindow::on_uan10_button_clicked()
{
    addCash(10,Utils::service);
}

void MainWindow::on_uan20_button_clicked()
{
     addCash(20,Utils::service);
}

void MainWindow::on_uan50_button_clicked()
{
    addCash(50,Utils::service);
}

void MainWindow::on_uan100_button_clicked()
{
    addCash(100,Utils::service);
}

void MainWindow::on_uan200_button_clicked()
{
    addCash(200,Utils::service);
}

void MainWindow::on_uan500_button_clicked()
{
    addCash(500,Utils::service);
}

void MainWindow::on_uan1000_button_clicked()
{
    addCash(1000,Utils::service);
}

void MainWindow::addCardData(QString data)
{

  if( ui->f1_button->isChecked()&& replaceAll(ui->card_number->text()+data).length()<17){
     ui->card_number->setText(ui->card_number->text()+data);
     if(replaceAll(ui->card_number->text()).length()==16)
        on_f2_clicked();
  }
  else if( ui->f2->isChecked()){
        if(ui->month_field->text().length()==0)
           ui->month_field->setText(ui->month_field->text()+data);
        else if(ui->month_field->text().length()==1 && data.toInt()<3)
           ui->month_field->setText(ui->month_field->text()+data);
        else if (ui->year_field->text().length()==0 && data.toInt()>1)
              ui->year_field->setText(ui->year_field->text()+data);
        else if(ui->year_field->text().length()==1){
              ui->year_field->setText(ui->year_field->text()+data);
              on_f3_clicked();
       }
  }
  else if( ui->f3->isChecked()){
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
    if(!Utils::cardNumberRegex.exactMatch(ui->card_number->text()))
    {
        ui->card_number->setStyleSheet(Utils::style_error);
    }
    else if(!Utils::monthRegex.exactMatch(ui->month_field->text()))
    {
        ui->month_field->setStyleSheet(Utils::style_error);
    }
    else if(!Utils::yearRegex.exactMatch(ui->year_field->text()))
    {
        ui->year_field->setStyleSheet(Utils::style_error);
    }
    else if(!Utils::cvv2Regex.exactMatch(ui->cvv2_field->text()))
    {
        ui->cvv2_field->setStyleSheet(Utils::style_error);
    }
    else{
        ui->stackedWidget->setCurrentIndex(4);
    }
}


void MainWindow::on_card_number_textChanged(const QString &)
{
    ui->card_number->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_month_field_textChanged(const QString &)
{
    ui->month_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_year_field_textChanged(const QString &)
{
    ui->year_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_cvv2_field_textChanged(const QString &)
{
    ui->cvv2_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_confirm_payment_clicked()
{
     ui->stackedWidget->setCurrentIndex(8);
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

void MainWindow::addNumber(QString num){
    if(ui->pin_field->text().length()<4)
        ui->pin_field->setText(ui->pin_field->text() + num);
}
void MainWindow::on_num_1_clicked()
{
    addNumber("1");
}
void MainWindow::on_num_2_clicked()
{
    addNumber("2");
}
void MainWindow::on_num_3_clicked()
{
    addNumber("3");
}
void MainWindow::on_num_4_clicked()
{
    addNumber("4");
}
void MainWindow::on_num_5_clicked()
{
    addNumber("5");
}
void MainWindow::on_num_6_clicked()
{
    addNumber("6");
}
void MainWindow::on_num_7_clicked()
{
    addNumber("7");
}
void MainWindow::on_num_8_clicked()
{
    addNumber("8");
}
void MainWindow::on_num_9_clicked()
{
    addNumber("9");
}
void MainWindow::on_num_0_clicked()
{
    addNumber("0");
}
void MainWindow::on_cl_onePin_clicked()
{
    ui->pin_field->backspace();
}
void MainWindow::on_cl_allPin_clicked()
{
    ui->pin_field->clear();
}
void MainWindow::on_pin_field_textChanged(const QString &)
{
    ui->pin_field->setStyleSheet(Utils::style_usual);
}
void MainWindow::printCheck( QString acc, QString card ,QString sum){
    double com;
    QString check;
    switch(Utils::service){
    case 0:
        com = countCommision(sum.toDouble(), Utils::service);
        check = card.length()>0 ? ( "Номер карти платника: " +card + '\n'+ "Сума платежу: "+ sum) : "Внесено готівки: " + sum  + '\n' + "Переведено: " + QString::number(sum.toDouble() - com);
        ui->check->setText("Номер мобільного рахунку: " +acc + '\n'+ check+ '\n' +"Сума комісії: " +QString::number(com) + '\n');
        break;
    case 1:
        com = countCommision(sum.toDouble(), Utils::service);
        check = card.length()>0 ? ( "Номер карти платника: " +card + '\n'+ "Сума платежу: "+ sum) : "Внесено готівки: " + sum  + '\n' + "Переведено: " + QString::number(sum.toDouble() - com);
        ui->check->setText("Номер карти отримувача: " +acc + '\n'+ check+ '\n' +"Сума комісії: " +QString::number(com) + '\n');
        break;
    case 2:
        com = countCommision(sum.toDouble(), Utils::service);
        check = card.length()>0 ? ( "Номер карти платника: " +card + '\n'+ "Сума платежу: "+ sum) : "Внесено готівки: " + sum  + '\n' + "Переведено: " + QString::number(sum.toDouble() - com);
        ui->check->setText("Отримувач: КП \"Київводоканал\"\nОсобовий номер рахунку платника: "+acc+'\n' + check+ '\n' +"Сума комісії: " +QString::number(com) + '\n');
        break;
    case 3:
        com = countCommision(sum.toDouble(), Utils::service);
        check = card.length()>0 ? ( "Номер карти платника: " +card + '\n'+ "Сума платежу: "+ sum) : "Внесено готівки: " + sum  + '\n' + "Переведено: " + QString::number(sum.toDouble() - com);
        ui->check->setText("Отримувач: Valve Corporation\nлогін Steam: "+acc+'\n' + check+ '\n' +"Сума комісії: " +QString::number(com) + '\n');
        break;
    }
}
void MainWindow::on_confirmPin_clicked()
{
    QString acc = ui->account_number->text();
    QString card = ui->card_number->text();
    QString month = ui->month_field->text();
    QString year = ui->year_field->text();
    QString cvv2 = ui->cvv2_field->text();
    QString pin = ui->pin_field->text();
    QString sum = ui->label_trans_sum->text();
    //TODO send payment request
    //
    bool success = true;
    if(success){
        printCheck(acc,card, sum);
        ui->stackedWidget->setCurrentIndex(6);
    }
    else{
         ui->stackedWidget->setCurrentIndex(7);
    }

}

void MainWindow::on_cancelPin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearFields();
}
void MainWindow::on_confirm_nal_payment_clicked()
{
    QString acc = ui->account_number->text();
    QString sum = ui->actual_cash_entered_label->text();
    //TODO send payment request
    //
    bool success = true;
    if(success){
        printCheck(acc, "", sum);
        ui->stackedWidget->setCurrentIndex(6);
    }
    else{
         ui->stackedWidget->setCurrentIndex(7);
    }

}

void MainWindow::on_label_trans_sum_textChanged(const QString &)
{
    ui->label_trans_sum->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_label_phone_number_textChanged(const QString &)
{
    ui->account_number->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_cancel_button_29_clicked()
{
    clearFields();
     ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_mob_button_clicked()
{
   ui->label_account_9->setText("Введіть номер телефону:");
   ui->account_number->setValidator(new QRegExpValidator(Utils::phoneRegex, this));
   Utils::service = 0;
   Utils::minNumberOfDigits = 10;
   Utils::maxNumberOfDigits = 12;
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_card_button_clicked()
{
    ui->label_account_9->setText("Введіть номер карти:");
    ui->account_number->setValidator(new QRegExpValidator(Utils::cardNumberRegex, this));
    Utils::service = 1;
    Utils::minNumberOfDigits = 16;
    Utils::maxNumberOfDigits = 16;
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_vodokanal_button_clicked()
{
    QFont font;
    font.setPointSize(14);
    ui->label_account_9->setFixedWidth(310);
    ui->label_account_9->setFont(font);
    ui->label_account_9->setText("Введіть номер особового рахунку:");
    ui->account_number->setValidator(new QRegExpValidator(Utils::digits, this));
    Utils::service = 2;
    Utils::minNumberOfDigits = 12;
    Utils::maxNumberOfDigits = 12;
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_steam_button_clicked()
{
    ui->label_account_9->setText("Введіть логін Steam:");
    ui->account_number->setValidator(new QRegExpValidator(Utils::login, this));
    Utils::service = 3;
    ui->stackedWidget->setCurrentIndex(1);
}
