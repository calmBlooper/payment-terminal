#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include<stdio.h>
#include <QFile>
#include <QTextStream>
#include "Utils.h"
#include "ServiceManager.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	servMan = new ServiceManager();
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
	delete servMan;
}

void MainWindow::clearFields() {
	ui->account_number->clear();
	ui->is_transfer_beznal->setChecked(false);
	ui->label_trans_sum->clear();
	ui->account_number->setPlaceholderText("");
	ui->actual_cash_entered_label->setText("0");
	ui->actual_cash_bez_com->setText("0");
	ui->account_number->setStyleSheet(Utils::style_usual);
	ui->confirm_nal_payment->setHidden(true);
	ui->cancel_payment_button->setHidden(false);
	ui->card_number->clear();
	ui->month_field->clear();
	ui->year_field->clear();
	ui->cvv2_field->clear();
	ui->pin_field->clear();
	ui->label_account_9->setFixedWidth(250);
	QFont font;
	font.setPointSize(15);
	ui->label_account_9->setFont(font);
	ui->servlistWidget->clear();
	ui->charity_beznal->setChecked(false);
	ui->charity_nal->setChecked(false);
}
QString replaceAll(QString str) {
	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == ' ' || str.at(i) == '(' || str.at(i) == ')')
			str.replace(i, 1, "");
	}
	return str;
}

void MainWindow::on_cancel_button_clicked()
{

	ui->stackedWidget->setCurrentIndex(0);
	clearFields();
}

void MainWindow::addTextToAccountField(QString str) {
	QString text = replaceAll(ui->account_number->text());
	if (text.length() <= Utils::maxNumberOfDigits)
		ui->account_number->setText(ui->account_number->text() + str);
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
	if (ui->account_number->text().length() == 0) {
		ui->account_number->setPlaceholderText("Введіть номер рахунку");
		ui->account_number->setStyleSheet(Utils::style_error);
	}
	else {

	}

	ui->account_number->setPlaceholderText("");
	ui->account_number->setStyleSheet(Utils::style_usual);

	if (ui->is_transfer_beznal->isChecked()) {
		ui->f1->setChecked(true);
		//get text about commision and max commision
		ui->beznalCommisionLabel->setText("");
		ui->stackedWidget->setCurrentIndex(3);
	}
	else {
		//get text about commision and max commision
		ui->nalCommisionLabel->setText("");
		ui->confirm_nal_payment->setHidden(true);
		ui->stackedWidget->setCurrentIndex(2);
	}

}

void MainWindow::on_cancel_sum_button_clicked()
{
	ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_cancel_payment_button_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	clearFields();
}
void MainWindow::validateSumOfTransfer(QString str) {
	QString temp = ui->label_trans_sum->text() + str;
	if (Utils::sumOfTransferRegex.exactMatch(temp))
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

double countCommision(int uan) {
	//count commison service name = Utils::service
	return 0;
}
void MainWindow::on_goto_pin_clicked()
{

	if (ui->label_trans_sum->text().length() == 0) {
		ui->label_trans_sum->setPlaceholderText("Введіть суму переказу");
		ui->label_trans_sum->setStyleSheet(Utils::style_error);
	}
	else {
		ui->label_trans_sum->setPlaceholderText("");
		ui->label_trans_sum->setStyleSheet(Utils::style_usual);
		double com = ui->label_trans_sum->text().toInt() + countCommision(ui->label_trans_sum->text().toInt());
		ui->account_data->setText("Номер рахунку: " + ui->account_number->text());
		ui->to_pay_sum->setText("Cума переказу: " + ui->label_trans_sum->text() + " грн");
		ui->card_data->setText("Номер карти: " + ui->card_number->text());
		ui->to_pay_data->setText("До сплати: " + QString::number(com) + " грн");
		ui->stackedWidget->setCurrentIndex(5);
	}
}

void MainWindow::on_cancel_button_16_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::addCash(int uan)
{
	ui->cancel_payment_button->setHidden(true);
	ui->confirm_nal_payment->setHidden(false);
	QString entered = ui->actual_cash_entered_label->text();
	int val1 = entered.toInt() + uan;
	if (val1 > 100000)
		return;
	ui->actual_cash_entered_label->setText(QString::number(val1));
	ui->actual_cash_bez_com->setText(QString::number(val1 - countCommision(val1)));

}
void MainWindow::on_uan5_button_clicked()
{
	addCash(5);
}

void MainWindow::on_uan10_button_clicked()
{
	addCash(10);
}

void MainWindow::on_uan20_button_clicked()
{
	addCash(20);
}

void MainWindow::on_uan50_button_clicked()
{
	addCash(50);
}

void MainWindow::on_uan100_button_clicked()
{
	addCash(100);
}

void MainWindow::on_uan200_button_clicked()
{
	addCash(200);
}

void MainWindow::on_uan500_button_clicked()
{
	addCash(500);
}

void MainWindow::on_uan1000_button_clicked()
{
	addCash(1000);
}

void MainWindow::addCardData(QString data)
{

	if (ui->f1->isChecked() && replaceAll(ui->card_number->text() + data).length() < 17) {
		ui->card_number->setText(ui->card_number->text() + data);
		if (replaceAll(ui->card_number->text()).length() == 16)
			on_f2_clicked();
	}
	else if (ui->f2->isChecked()) {
		if (ui->month_field->text().length() == 0)
			ui->month_field->setText(ui->month_field->text() + data);
		else if (ui->month_field->text().length() == 1 && data.toInt() < 3)
			ui->month_field->setText(ui->month_field->text() + data);
		else if (ui->year_field->text().length() == 0 && data.toInt() > 1)
			ui->year_field->setText(ui->year_field->text() + data);
		else if (ui->year_field->text().length() == 1) {
			ui->year_field->setText(ui->year_field->text() + data);
			on_f3_clicked();
		}
	}
	else if (ui->f3->isChecked()) {
		ui->cvv2_field->setText(ui->cvv2_field->text() + data);
	}
}


void MainWindow::on_f1_clicked()
{
	ui->f1->setChecked(true);
	ui->f2->setChecked(false);
	ui->f3->setChecked(false);
}

void MainWindow::on_f2_clicked()
{
	ui->f1->setChecked(false);
	ui->f2->setChecked(true);
	ui->f3->setChecked(false);
}

void MainWindow::on_f3_clicked()
{
	ui->f1->setChecked(false);
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
	if (ui->f1->isChecked()) {
		ui->card_number->backspace();
	}
	if (ui->f2->isChecked()) {
		if (ui->year_field->text().length() > 0)
			ui->year_field->backspace();
		else if (ui->month_field->text().length() > 0)
			ui->month_field->backspace();
	}
	if (ui->f3->isChecked()) {
		ui->cvv2_field->backspace();
	}
}

void MainWindow::on_cl_all_data_clicked()
{
	if (ui->f1->isChecked()) {
		ui->card_number->clear();
	}
	if (ui->f2->isChecked()) {
		ui->year_field->clear();
		ui->month_field->clear();
	}
	if (ui->f3->isChecked()) {
		ui->cvv2_field->clear();
	}
}

void MainWindow::on_goto_transfer_details_clicked()
{
	ui->rec_err_lab->hide();
	if (!Utils::cardNumberRegex.exactMatch(ui->card_number->text()))
	{
		ui->card_number->setStyleSheet(Utils::style_error);
	}
	else if (!Utils::monthRegex.exactMatch(ui->month_field->text()))
	{
		ui->month_field->setStyleSheet(Utils::style_error);
	}
	else if (!Utils::yearRegex.exactMatch(ui->year_field->text()))
	{
		ui->year_field->setStyleSheet(Utils::style_error);
	}
	else if (!Utils::cvv2Regex.exactMatch(ui->cvv2_field->text()))
	{
		ui->cvv2_field->setStyleSheet(Utils::style_error);
	}
	else {
		try {
			servMan->setSenderPaycard(
				ui->card_number->text().toStdString(),
				ui->cvv2_field->text().toInt(),
				ui->month_field->text().toInt(),
				ui->year_field->text().toInt());
			ui->stackedWidget->setCurrentIndex(4);
		}
		catch (const CredentialsError& e) {
			ui->rec_err_lab->setText(QString::fromStdString(e.getReason()));
			ui->rec_err_lab->show();
		}


	}
}


void MainWindow::on_card_number_textChanged(const QString&)
{
	ui->card_number->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_month_field_textChanged(const QString&)
{
	ui->month_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_year_field_textChanged(const QString&)
{
	ui->year_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_cvv2_field_textChanged(const QString&)
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

void MainWindow::addNumber(QString num) {
	if (ui->pin_field->text().length() < 4)
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
void MainWindow::on_pin_field_textChanged(const QString&)
{
	ui->pin_field->setStyleSheet(Utils::style_usual);
}
void MainWindow::printCheck(QString acc, QString card, QString sum) {
	//create check string
	ui->check->setText("");
}
void MainWindow::on_confirmPin_clicked()
{
	QString acc = ui->account_number->text();
	QString card = ui->card_number->text();
	QString month = ui->month_field->text();
	QString year = ui->year_field->text();
	QString cvv = ui->cvv2_field->text();
	QString pin = ui->pin_field->text();
	QString sum = ui->label_trans_sum->text();
	
	bool success = true;
	if (success) {
		printCheck(acc, card, sum);
		ui->stackedWidget->setCurrentIndex(6);
	}
	else {
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
	if (success) {
		printCheck(acc, "", sum);
		ui->stackedWidget->setCurrentIndex(6);
	}
	else {
		ui->stackedWidget->setCurrentIndex(7);
	}

}

void MainWindow::on_label_trans_sum_textChanged(const QString&)
{
	ui->label_trans_sum->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_account_number_textChanged(const QString&)
{
	ui->account_number->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_cancel_button_29_clicked()
{
	ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::execService() {
	QFont font;
	switch (servMan->getCurrentServiceType()) {
	case ServiceType::Communication:
		ui->label_account_9->setText("Введіть номер телефону:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::phoneRegex, this));
		Utils::maxNumberOfDigits = 12;
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Banking:
		font.setPointSize(14);
		ui->label_account_9->setFont(font);
		ui->label_account_9->setFixedWidth(310);
		ui->label_account_9->setText("Введіть номер рахунку отримувача:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::cardNumberRegex, this));
		Utils::maxNumberOfDigits = 16;
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Utilities:
		font.setPointSize(14);
		ui->label_account_9->setFixedWidth(310);
		ui->label_account_9->setFont(font);
		ui->label_account_9->setText("Введіть номер особового рахунку:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::digits, this));
		Utils::maxNumberOfDigits = 12;
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Gaming:
		ui->label_account_9->setText("Введіть логін:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::login, this));
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Charity:
		ui->stackedWidget->setCurrentIndex(10);
		break;

	}

}
void MainWindow::on_mob_button_clicked()
{
	Utils::service = "Поповнення мобільного";
	servMan->setCurrentServiceType(ServiceType::Communication);
	execService();
}


void MainWindow::on_card_button_clicked()
{
	Utils::service = "Переказ на карту";
	servMan->setCurrentServiceType(ServiceType::Banking);
	execService();
}

void MainWindow::on_vodokanal_button_clicked()
{
	Utils::service = "Київводоканал";
	servMan->setCurrentServiceType(ServiceType::Utilities);
	execService();

}
void MainWindow::on_steam_button_clicked()
{
	Utils::service = "Поповнення Steam";
	servMan->setCurrentServiceType(ServiceType::Gaming);
	execService();
}
void MainWindow::renderElementsInFolder(QList<QString>& list) {
	for (int i = 0; i < list.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		QIcon icon(list.at(i));
		item->setIcon(icon);
		item->setStatusTip(QString::number(i));
		ui->servlistWidget->addItem(item);
	}
	ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_servlistWidget_itemClicked(QListWidgetItem* item)
{
	//std::cout<<item->statusTip().toStdString()<<std::endl;
	QString serviceName = item->statusTip();
	// get service by name

	execService();


}

void MainWindow::on_mob_folder_button_clicked()
{
	QString folderName("Мобільні послуги");
	servMan->setCurrentServiceType(ServiceType::Communication);
	QList<QString> servicesList;
	//servicesList should be replaced with real list
	servicesList.append(":/icons/10_грн.jpg");

	renderElementsInFolder(servicesList);
}

void MainWindow::on_backToMainMenu_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	ui->servlistWidget->clear();
}

void MainWindow::on_bank_folder_button_clicked()
{
	QString folderName("Платіжні системи");
	servMan->setCurrentServiceType(ServiceType::Banking);
	QList<QString> servicesList;
	servicesList.append(":/icons/20_грн.png");
	renderElementsInFolder(servicesList);
}

void MainWindow::on_com_folder_button_clicked()
{
	QString folderName("Комунальні послуги");
	servMan->setCurrentServiceType(ServiceType::Utilities);
	QList<QString> servicesList;
	servicesList.append(":/icons/5_грн.jpg");
	renderElementsInFolder(servicesList);
}

void MainWindow::on_game_folder_button_clicked()
{
	QString folderName("Ігри");
	servMan->setCurrentServiceType(ServiceType::Gaming);
	QList<QString> servicesList;
	servicesList.append(":/icons/50_грн.png");
	renderElementsInFolder(servicesList);
}

void MainWindow::on_charity_folder_button_clicked()
{
	QString folderName("Благодійність");
	servMan->setCurrentServiceType(ServiceType::Charity);
	QList<QString> servicesList;
	servicesList.append(":/icons/100_грн.jpg");
	renderElementsInFolder(servicesList);
}


void MainWindow::on_charity_nal_clicked()
{
	if (ui->charity_nal->checkState())
		ui->charity_beznal->setChecked(false);
	ui->charity_cancel->hide();
}

void MainWindow::on_charity_beznal_clicked()
{
	if (ui->charity_beznal->checkState())
		ui->charity_nal->setChecked(false);
	ui->charity_cancel->hide();
}

void MainWindow::on_charity_cancel_clicked()
{
	ui->charity_beznal->setChecked(false);
	ui->charity_nal->setChecked(false);
	ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_charity_continue_clicked()
{

	if (ui->charity_nal->checkState())
	{
		ui->stackedWidget->setCurrentIndex(2);
		ui->nalCommisionLabel->setText("");
	}
	if (ui->charity_beznal->checkState()) {
		ui->f1->setChecked(true);
		//get text about commision and max commision
		ui->beznalCommisionLabel->setText("");
		ui->stackedWidget->setCurrentIndex(3);
	}
}

void MainWindow::on_about_button_clicked()
{
	QFile file(":/about/About.txt");
	QTextStream in(&file);
	file.open(QIODevice::ReadOnly);
	ui->textBrowser->setText(in.readAll());
	std::cout << in.readAll().toStdString() << std::endl;
	ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_about_back_button_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	ui->textBrowser->clear();
}

void MainWindow::on_cancelTransfer_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	clearFields();
}