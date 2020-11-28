#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRegExpValidator>
#include<stdio.h>
#include <QFile>
#include <QTextStream>
#include "Utils.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	servMan = new ServiceManager();
	ui->setupUi(this);
	ui->card_number->setValidator(new QRegExpValidator(Utils::cardNumberRegex, this));
	ui->month_field->setValidator(new QRegExpValidator(Utils::monthRegex, this));
	ui->year_field->setValidator(new QRegExpValidator(Utils::yearRegex, this));
	ui->cvv2_field->setValidator(new QRegExpValidator(Utils::cvv2Regex, this));
	ui->label_trans_sum->setValidator(new QRegExpValidator(Utils::sumOfTransferRegex, this));
	ui->pin_field->setValidator(new QRegExpValidator(Utils::pinRegex, this));
	ui->label_address->hide();
	ui->address_field->hide();
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
	ui->address_field->setPlaceholderText("");
	ui->address_field->clear();
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
	servMan->endSession();
	ui->label_address->hide();
	ui->address_field->setStyleSheet(Utils::style_usual);
	ui->address_field->hide();
	ui->com_err_lab->hide();
	Utils::pin_times = 3;
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
	if (servMan->getCurrentServiceType() == ServiceType::Utilities && ui->address_field->text().length() == 0)
	{
		ui->address_field->setPlaceholderText("Введіть дані");
		ui->address_field->setStyleSheet(Utils::style_error);
		return;
	}
	if (ui->account_number->text().length() == 0)
	{
		ui->account_number->setPlaceholderText("Введіть дані");
		ui->account_number->setStyleSheet(Utils::style_error);
		return;
	}
	else
	{
		QString name;
		QString address;
		try
		{
			switch (servMan->getCurrentServiceType())
			{
			case ServiceType::Communication:
				servMan->setRecipientMobileAccount(ui->account_number->text().toLocal8Bit().constData());
				break;
			case ServiceType::Banking:
				if (QString::fromLocal8Bit(servMan->getCurrentServiceName().c_str()).endsWith("ПриватБанк"))
					servMan->setRecipientPaycard(ui->account_number->text().toLocal8Bit().constData());
				else
					servMan->setRecipientEWalletAccount(ui->account_number->text().toLocal8Bit().constData());
				break;
			case ServiceType::Utilities:
				name = ui->account_number->text();
				address = ui->address_field->text();
				servMan->setRecipientPublicAccount(name.toLocal8Bit().constData(), address.toLocal8Bit().constData());
				break;
			case ServiceType::Gaming:
				servMan->setRecipientPublicAccount(ui->account_number->text().toLocal8Bit().constData());
				break;

			}
		}
		catch (const CredentialsError& err)
		{
			QFont font;
			font.setPixelSize(18);
			ui->com_err_lab->setText(err.getReason());
			ui->com_err_lab->setFont(font);
			ui->com_err_lab->setStyleSheet(Utils::exeption_style);
			ui->com_err_lab->show();
			return;
		}
	}
	ui->com_err_lab->hide();
	ui->account_number->setPlaceholderText("");
	ui->account_number->setStyleSheet(Utils::style_usual);
	if (ui->is_transfer_beznal->isChecked())
	{
		ui->f1->setChecked(true);
		ui->beznalCommisionLabel->setText("");//TODO get text about commision and max commision
		ui->card_err_lab->hide();
		ui->stackedWidget->setCurrentIndex(3);
	}
	else
	{
		ui->nalCommisionLabel->setText("");//TODO get text about commision and max commision
		ui->confirm_nal_payment->setHidden(true);
		ui->stackedWidget->setCurrentIndex(2);
	}

}
void MainWindow::on_confirm_nal_payment_clicked()
{
	QString sum = ui->actual_cash_entered_label->text();
	try {
		servMan->processTransfer(sum.toDouble());
		printCheck(sum.toDouble());
		ui->stackedWidget->setCurrentIndex(5);
	}
	catch (const TransferError&) {
		ui->stackedWidget->setCurrentIndex(6);
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

void MainWindow::on_cancel_button_16_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::addCash(int uan)
{
	ui->cancel_payment_button->setHidden(true);
	ui->confirm_nal_payment->setHidden(false);
	int val1 = ui->actual_cash_entered_label->text().toInt() + uan;
	if (val1 > 20000)
		return;
	ui->actual_cash_entered_label->setText(QString::number(val1));
	ui->actual_cash_bez_com->setText(QString::number(servMan->realTransferredAmount(val1)));

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
		if (Utils::monthRegex.exactMatch(ui->month_field->text() + data))
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
		try
		{
			servMan->setSenderPaycard(
				ui->card_number->text().toLocal8Bit().constData(),
				ui->cvv2_field->text().toInt(),
				ui->month_field->text().toInt(),
				ui->year_field->text().toInt());
		}
		catch (const CredentialsError& err)
		{
			QFont font;
			font.setPixelSize(18);
			ui->card_err_lab->setText(err.getReason());
			ui->card_err_lab->setFont(font);
			ui->card_err_lab->setStyleSheet(Utils::exeption_style);
			ui->card_err_lab->show();
			return;
		}
		ui->card_err_lab->hide();
		ui->stackedWidget->setCurrentIndex(4);
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
	if (ui->label_trans_sum->text().length() == 0) {
		ui->label_trans_sum->setPlaceholderText("Введіть суму переказу");
		ui->label_trans_sum->setStyleSheet(Utils::style_error);
		return;
	}
	if (ui->label_trans_sum->text().toDouble() < servMan->minimumAmount()) {
		ui->label_trans_sum->setPlaceholderText("Мінімальна сума переказу: " + QString::number(servMan->minimumAmount()));
		ui->label_trans_sum->setStyleSheet(Utils::style_error);
		return;
	}
	ui->pin_err_lab->hide();
	ui->stackedWidget->setCurrentIndex(7);
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
void MainWindow::printCheck(const double& amount) {

	ui->check->setText(servMan->getReceipt(amount));
}
void MainWindow::on_confirmPin_clicked()
{
	QString pin = ui->pin_field->text();
	QString sum = ui->label_trans_sum->text();

	bool valid = servMan->validateSenderPin(pin.toInt());
	if (!valid) {
		//add text to error label
		QFont font;
		font.setPixelSize(18);
		ui->pin_err_lab->setText("Невірний PIN-код, залишилось спроб: " + QString::number(--Utils::pin_times));
		ui->pin_err_lab->setFont(font);
		ui->pin_err_lab->setStyleSheet(Utils::exeption_style);
		ui->pin_err_lab->show();
		
		if (Utils::pin_times == 0) 
		{
			clearFields();
			ui->stackedWidget->setCurrentIndex(0);

		}
		ui->pin_err_lab->show();
		return;
	}
	ui->pin_err_lab->hide();
	try
	{
		servMan->processTransfer(sum.toDouble());
		printCheck(sum.toDouble());
		ui->stackedWidget->setCurrentIndex(5);
	}
	catch (const TransferError&)
	{
		ui->stackedWidget->setCurrentIndex(6);
	}

}

void MainWindow::on_cancelPin_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	clearFields();
}

void MainWindow::on_label_trans_sum_textChanged(const QString&)
{
	ui->label_trans_sum->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_account_number_textChanged(const QString&)
{
	ui->account_number->setStyleSheet(Utils::style_usual);
}
void MainWindow::on_address_field_textChanged(const QString&)
{
	ui->address_field->setStyleSheet(Utils::style_usual);
}

void MainWindow::on_cancel_button_29_clicked()
{
	ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::execService() {
	QFont font;
	ui->com_err_lab->hide();
	switch (servMan->getCurrentServiceType()) {
	case ServiceType::Communication:
		ui->label_account_9->setText("Введіть номер телефону:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::phoneRegex, this));
		Utils::maxNumberOfDigits = 12;
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Banking:
		font.setPointSize(14);
		ui->label_account_9->setFixedWidth(320);
		ui->label_account_9->setFont(font);
		ui->label_account_9->setText("Введіть номер рахунку отримувача:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::login, this));
		Utils::maxNumberOfDigits = 16;
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Utilities:
		font.setPointSize(14);
		ui->label_account_9->setFixedWidth(250);
		ui->label_account_9->setFont(font);
		ui->label_account_9->setText("Введіть ПІБ (повністю):");
		ui->label_address->show();
		ui->address_field->show();
		ui->account_number->setValidator(new QRegExpValidator(Utils::any, this));
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Gaming:
		ui->label_account_9->setText("Введіть логін:");
		ui->account_number->setValidator(new QRegExpValidator(Utils::login, this));
		ui->stackedWidget->setCurrentIndex(1);
		break;
	case ServiceType::Charity:
		//add receiver name such as 'Фонд таблєточкі'
		ui->stackedWidget->setCurrentIndex(9);
		break;

	}

}
void MainWindow::on_mob_button_clicked()
{
	Utils::service = "Поповнення мобільного";
	servMan->setCurrentServiceType(ServiceType::Communication);
	servMan->setCurrentService(QString("Київстар").toLocal8Bit().constData());
	execService();
}


void MainWindow::on_card_button_clicked()
{
	Utils::service = "Переказ на карту";
	servMan->setCurrentServiceType(ServiceType::Banking);
	servMan->setCurrentService(QString("ПриватБанк").toLocal8Bit().constData());
	execService();
}

void MainWindow::on_vodokanal_button_clicked()
{
	Utils::service = "Київводоканал";
	servMan->setCurrentServiceType(ServiceType::Utilities);
	servMan->setCurrentService(QString("Київводоканал").toLocal8Bit().constData());
	execService();

}
void MainWindow::on_steam_button_clicked()
{
	Utils::service = "Поповнення Steam";
	servMan->setCurrentServiceType(ServiceType::Gaming);
	servMan->setCurrentService(QString("Поповнення гаманця Steam").toLocal8Bit().constData());
	execService();
}
struct MainWindow::FolderService {
	QString icon;
	QString service;
};
void MainWindow::renderElementsInFolder(QList<FolderService>& list) {
	for (int i = 0; i < list.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		QIcon icon(list.at(i).icon);
		item->setIcon(icon);
		item->setStatusTip(list.at(i).service);
		ui->servlistWidget->addItem(item);
	}
	ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_servlistWidget_itemClicked(QListWidgetItem* item)
{
	QString name = item->statusTip();
	servMan->setCurrentService(name.toLocal8Bit().constData());

	execService();
}

void MainWindow::on_mob_folder_button_clicked()
{
	QString folderName("Мобільні послуги");
	servMan->setCurrentServiceType(ServiceType::Communication);
	QList<FolderService> servicesList;
	FolderService serv;
	serv.icon = ":/icons/kiyvstar.png";
	serv.service = "Київстар";
	servicesList.append(serv);
	serv.icon = ":/icons/vodafone.png";
	serv.service = "Vodafone";
	servicesList.append(serv);
	serv.icon = ":/icons/lifecell.png";
	serv.service = "lifecell (Life)";
	servicesList.append(serv);


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
	QList<FolderService> servicesList;
	FolderService serv;
	serv.icon = ":/icons/privatBank.png";
	serv.service = "ПриватБанк";
	servicesList.append(serv);
	serv.icon = ":/icons/paypal.png";
	serv.service = "PayPal";
	servicesList.append(serv);
	serv.icon = ":/icons/webmoney.png";
	serv.service = "WebMoney";
	servicesList.append(serv);
	renderElementsInFolder(servicesList);
}

void MainWindow::on_com_folder_button_clicked()
{
	QString folderName("Комунальні послуги");
	servMan->setCurrentServiceType(ServiceType::Utilities);
	QList<FolderService> servicesList;
	FolderService serv;
	serv.icon = ":/icons/kvod.png";
	serv.service = "Київводоканал";
	servicesList.append(serv);
	serv.icon = ":/icons/tsifral.png";
	serv.service = "Цифрал сервіс";
	servicesList.append(serv);
	renderElementsInFolder(servicesList);
}

void MainWindow::on_game_folder_button_clicked()
{
	QString folderName("Ігри");
	servMan->setCurrentServiceType(ServiceType::Gaming);
	QList<FolderService> servicesList;
	FolderService serv;
	serv.icon = ":/icons/gta_card.png";
	serv.service = "GTA Online Shark Cards";
	servicesList.append(serv);
	serv.icon = ":/icons/starWars.png";
	serv.service = "STAR WARS™: The Old Republic™";
	servicesList.append(serv);
	serv.icon = ":/icons/warthunder.png";
	serv.service = "Warthunder";
	servicesList.append(serv);
	serv.icon = ":/icons/steam_icon.png";
	serv.service = "Поповнення гаманця Steam";
	servicesList.append(serv);
	renderElementsInFolder(servicesList);
}

void MainWindow::on_charity_folder_button_clicked()
{
	QString folderName("Благодійність");
	servMan->setCurrentServiceType(ServiceType::Charity);
	ui->card_err_lab->hide();
	QList<FolderService> servicesList;
	FolderService serv;
	serv.icon = ":/icons/ubb.png";
	serv.service = "Українська Біржа Благодійності";
	servicesList.append(serv);
	serv.icon = ":/icons/jw.png";
	serv.service = "Всесвітній Центр Свідків Єгови";
	servicesList.append(serv);
	serv.icon = ":/icons/chkh.png";
	serv.service = "Червоний хрест";
	servicesList.append(serv);
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
	clearFields();
	ui->stackedWidget->setCurrentIndex(0);
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
	std::cout << in.readAll().toLocal8Bit().constData() << std::endl;
	ui->stackedWidget->setCurrentIndex(10);
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
