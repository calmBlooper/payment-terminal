#include "approvepaymentpage.h"
#include "ui_approvepaymentpage.h"
#include <QRegExpValidator>

int ApprovePaymentPage::tries = 3;
ApprovePaymentPage::ApprovePaymentPage(QString account,QString card,QString sum, QString year,QString month,QString cvv2, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApprovePaymentPage),
     account(account),
     cardNumber(card),
     sum(sum),
     year(year),
     month(month),
     cvv2(cvv2)
{
    ui->setupUi(this);
    QRegExp pinRegex ("[0-9][0-9][0-9][0-9]");
    QRegExpValidator *cardValidator = new QRegExpValidator(pinRegex, this);
    ui->pin_field->setValidator(cardValidator);
}

ApprovePaymentPage::~ApprovePaymentPage()
{
    delete ui;
}
void ApprovePaymentPage::addNumber(QString num){
    if(ui->pin_field->text().length()<4)
        ui->pin_field->setText(ui->pin_field->text() + num);
}
void ApprovePaymentPage::on_num_1_clicked()
{
    addNumber("1");
}
void ApprovePaymentPage::on_num_2_clicked()
{
    addNumber("2");
}
void ApprovePaymentPage::on_num_3_clicked()
{
    addNumber("3");
}
void ApprovePaymentPage::on_num_4_clicked()
{
    addNumber("4");
}
void ApprovePaymentPage::on_num_5_clicked()
{
    addNumber("5");
}
void ApprovePaymentPage::on_num_6_clicked()
{
    addNumber("6");
}
void ApprovePaymentPage::on_num_7_clicked()
{
    addNumber("7");
}
void ApprovePaymentPage::on_num_8_clicked()
{
    addNumber("8");
}
void ApprovePaymentPage::on_num_9_clicked()
{
    addNumber("9");
}
void ApprovePaymentPage::on_num_0_clicked()
{
    addNumber("0");
}
void ApprovePaymentPage::on_cl_one_clicked()
{
    ui->pin_field->backspace();
}
void ApprovePaymentPage::on_cl_all_clicked()
{
    ui->pin_field->clear();
}

void ApprovePaymentPage::on_accept_clicked()
{

    if(ui->pin_field->text().length()<4)
        ui->pin_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                     " border-width: 5px;"
                                     " border-radius: 10px;"
                                     " border-color:  red;"
                                     " border-style:solid;"
                                     " outline: 0;");
    else
    {
        //send request to validate card
        //execute actual transfer
        bool exec = true;
        if(exec){
           this->accept();
        }
        else if(tries>1)
        {
            ui->label->setText("Pin-код неправильний. Залишилось спроб: " + QString::number(--tries));
        }
        else
            this->reject();
    }
}

void ApprovePaymentPage::on_pin_field_textChanged(const QString &)
{
    ui->pin_field->setStyleSheet("background-color: rgb(255, 255, 255);"
                                 " border-width: 3px;"
                                 " border-radius: 10px;"
                                 " border-color: #331E38;"
                                 " border-style:solid;"
                                 " outline: 0;");
}

void ApprovePaymentPage::on_pushButton_clicked()
{
    this->accept();
}

void ApprovePaymentPage::on_pushButton_2_clicked()
{
     this->accept();
}
