#pragma once
#pragma once
#include "DBManager.h"
#include <string>
#include <sstream>
#include <ctime>
typedef enum {
	Communication = 0,
	Banking,
	Utilities,
	Gaming,
	Charity
} ServiceType;
class CredentialsError {

private:

	const std::string _reason;
public:

	CredentialsError(std::string reason = "") :_reason(reason) {
		return;
	}
	const std::string& getReason() {
		return _reason;
	}
};
class TransferError {

private:

	const std::string _reason;

public:

	TransferError(std::string reason = "") :_reason(reason) {
		return;
	}
	const std::string& getReason() {
		return _reason;
	}
};
class ServiceManager {
private:



	MobileAccount* recipientMobileAccount;

	Paycard* recipientPaycard;

	PublicAccount* recipientPublicAccount;

	EWalletAccount* recipientEWalletAccount;

	Service* currentService;

	ServiceType* currentServiceType;

	Paycard* currentSenderPaycard;

	DBManager database;

	std::string generateReceiptNumber() {
		std::ostringstream os;
		for (int i = 0; i < 12; ++i)
		{
			int digit = rand() % 10;
			os << digit;
		}
		return os.str();
	}

	std::string generateEDRPOU() {
		std::ostringstream os;
		for (int i = 0; i < 8; ++i)
		{
			int digit = rand() % 10;
			os << digit;
		}
		return os.str();
	}
	std::string generateTransactionCode() {
		std::ostringstream os;
		os << "M";
		for (int i = 0; i < 8; ++i)
		{
			int digit = rand() % 10;
			os << digit;
		}
		os << "L";
		return os.str();
	}
	void sendMoney(const double& amount) {
		if (recipientEWalletAccount != nullptr) {
			recipientEWalletAccount->replenish(realTransferredAmount(amount), Currency::UAH);
			database.getEWalletRepAcc().update(*recipientEWalletAccount);
			return;
		}
		if (recipientMobileAccount != nullptr) {
			recipientEWalletAccount->replenish(realTransferredAmount(amount), Currency::UAH);
			database.getMobileRepAcc().update(*recipientMobileAccount);
			return;
		}
		if (recipientPaycard != nullptr) {
			PrivateAccount recipientPrivateAccount = database.getPrivateRepAcc().getById(recipientPaycard->getAccountId());
			recipientPrivateAccount.replenish(realTransferredAmount(amount), Currency::UAH);
			database.getPrivateRepAcc().update(recipientPrivateAccount);
			return;
		}
		if (recipientPublicAccount != nullptr) {
			recipientPublicAccount->replenish(realTransferredAmount(amount), Currency::UAH);
			database.getPublicRepAcc().update(*recipientPublicAccount);
			return;
		}
	}
	const char* currentTime() {
		std::time_t ct = std::time(0);
		char* cc = ctime(&ct);
		return cc;
	}
public:

	ServiceManager() {
		resetAllCurrentInfo();
		//TODO: upload data to database, or nothing if database is already filled
		return;
	}

	~ServiceManager() {
		resetAllCurrentInfo();
		return;
	}



	const std::string getServiceImageURL(const std::string& serviceName) {
		//TODO: Insert proper path and image format
		return "[base folder path or web-address, containing all the images]/" + serviceName + ".jpg or whatever format";
	}

	void setCurrentService(const std::string& serviceName) {
		currentService = new Service(database.getServiceRep().getByKey(serviceName));
	}

	const Service* getCurrentService() const {
		return currentService;
	}

	void setCurrentServiceType(const ServiceType& type) {
		currentServiceType = new ServiceType(type);
	}

	const ServiceType* getCurrentServiceType() const {
		return currentServiceType;
	}

	//Use when all the required credentials have been entered and you are ready to work with this account.
	/*
	const Account* getCurrentRecipientAccount() {
		return currentRecipientAccount;
	}
	*/
	//Resets current account, service type and service itself. Useful expecially at the end of session
	void resetAllCurrentInfo() {
		recipientMobileAccount = nullptr;
		recipientEWalletAccount = nullptr;
		recipientPaycard = nullptr;
		recipientPublicAccount = nullptr;
		currentService = nullptr;
		currentServiceType = nullptr;
		currentSenderPaycard = nullptr;
	}

	const std::vector <Service> loadServicesByType(const std::string& serviceType) {
		if (!serviceType.compare("�������� ��'����")) setCurrentServiceType(ServiceType::Communication);
		if (!serviceType.compare("������ �������"))  setCurrentServiceType(ServiceType::Banking);
		if (!serviceType.compare("��������� �������")) setCurrentServiceType(ServiceType::Utilities);
		if (!serviceType.compare("����")) setCurrentServiceType(ServiceType::Gaming);
		if (!serviceType.compare("�����������")) setCurrentServiceType(ServiceType::Charity);
		return database.getServiceRep().getByType(*currentServiceType);
		throw "Unknown service type!";
	}

	//Used with both ewallets and games
	void setRecipientEWalletAccount(const std::string& credentials) {
		EWalletAccount* result = new EWalletAccount(database.getEWalletRepAcc().getByLogin(credentials));
		if (result->getId() == 0)  result = new EWalletAccount(database.getEWalletRepAcc().getByEmail(credentials));
		if (result->getId() == 0) throw CredentialsError("���� �����, �������� ���� ��������. ���� ���������.");
		recipientEWalletAccount = new EWalletAccount(*result);
		delete result;
	};
	void setRecipientPublicAccount(const std::string& name) {
		PublicAccount result = database.getPublicRepAcc().getByKey(name);
		if (result.getId() == 0) throw CredentialsError("���� �����, �������� ���� ��������. ���� ���������.");
	}
	void setRecipientPublicAccount(const std::string& name, const std::string& address) {
		PublicAccount result = database.getPublicRepAcc().getByKey(name);
		if (result.getId() == 0 || result.getAddress().compare(address)) throw CredentialsError("���� �����, �������� ���� ��������. ���� ���������.");
	}

	void setSenderPaycard(const std::string& cardNumber, const __int32& cvv,
		const __int32& expMonth,
		const __int32& expYear) {
		Paycard result = database.getPaycardRep().getByKey(cardNumber);
		if (result.getId() == 0) throw CredentialsError("������ �������� ����� ������.");
		if (result.getExpMonth() != expMonth || result.getExpYear() != expYear || result.getCvv() != cvv) throw  CredentialsError("���� �����, �������� ���� ��������. ���� ���������.");
		currentSenderPaycard = new Paycard(result);
	};

	void setRecipientPaycard(const std::string& cardNumber) {
		Paycard result = database.getPaycardRep().getByKey(cardNumber);
		if (result.getId() == 0) throw CredentialsError("������ �������� ����� ������.");
		recipientPaycard = new Paycard(result);
	}

	void setRecipientMobileAccount(const std::string& number) {
		MobileAccount result = database.getMobileRepAcc().getByKey(number);
		if (result.getId() == 0) throw CredentialsError("���� �����, �������� ���� ��������. ���� ���������.");
		recipientMobileAccount = new MobileAccount(result);
	}

	double commissionPercentage() {
		return currentService->getCommission();
	}

	double minimumAmount() {
		if (*currentServiceType == ServiceType::Communication) return 5;
		return 10;
	}

	double maxCommission() {
		if (currentSenderPaycard == nullptr) return 250;
		if (*currentServiceType == ServiceType::Charity) return 50;
		return -1;
	}

	void processTransfer(const double& amount) {
		if (amount < minimumAmount()) {
			if (currentSenderPaycard == nullptr) throw TransferError("���� �����, ������ ����� ����.");
			throw TransferError("���� �����, ������ ����� ����.");
		}
		if (currentSenderPaycard == nullptr) {
			sendMoney(amount);
			return;
		}
		if (amount > 50000.0) throw TransferError("����� ������ ���� ��������. ���� �����, ������ ���� ����� 50000 ���.");
		PrivateAccount senderAccount = database.getPrivateRepAcc().getById(currentSenderPaycard->getAccountId());
		if (amount > senderAccount.getBalance()) throw TransferError("����������� ����� �� ������. ���� �����, ������ ����� ����");
		senderAccount.dismount(amount, Currency::UAH);
		database.getPrivateRepAcc().update(senderAccount);
		sendMoney(amount);
	}

	double realTransferredAmount(const double& amount) {
		double commission = amount / 100.0 * commissionPercentage();
		if (commission > maxCommission()) return amount - maxCommission();
		return amount - commission;
	}

	std::string doubleToSTDString(const double& number) {
		std::ostringstream os;
		os << number;
		return os.str();
	}

	std::string getReceipt(const double& amount) {
		std::string result = "���������: " + generateReceiptNumber() + "\n" +
			"�������: 8662957\n" +
			"��� ��������: " + generateTransactionCode() + "\n" +
			"������: ������ ������ ������, 14�\n" +
			"==================================================\n"+
			"��������: " + doubleToSTDString(amount) + " ���" + "\n" +
			"���������� ����������: " + doubleToSTDString(realTransferredAmount(amount)) + " ���" + "\n" +
			"�����: " + doubleToSTDString(amount - realTransferredAmount(amount)) + " ��� " + "\n" +
			"����: " + currentTime() + "\n"+
			"==================================================\n" ;
		if (recipientMobileAccount != nullptr) result += "����� ��������: " + recipientMobileAccount->getNumber() + "\n" +
			"����������� �������: ������ ������ ��������� ��'����" + "\n";
		else if (recipientEWalletAccount != nullptr) result += "�������������: " + recipientEWalletAccount->getLogin() + "\n" +
			"����������� �������: ������ ����������� ������" + "\n";
		else if (recipientPaycard != nullptr) result += "����� ������� ����������: " + recipientPaycard->getCardNumber() + "\n" +
			"����������� �������: �������� �������" + "\n";
		else if (recipientPublicAccount != nullptr) {
			if (*currentServiceType == ServiceType::Utilities) result += "��'� ��������: " + recipientPublicAccount->getName() + "\n" +
				"������ ��������: " + recipientPublicAccount->getAddress() + "\n" +
				"����������� �������: ������ ����������� ������" + "\n";
			else result += "����� ����������: " + recipientPublicAccount->getName() + "\n" +
				"����������� �������: �����������" + "\n";
		}
		result += "==================================================\n";
		if (*currentServiceType == ServiceType::Communication || *currentServiceType == ServiceType::Banking || *currentServiceType == ServiceType::Utilities) result += "���������: ��� \"" + currentService->getName() + "\"" + "\n";
		else {
			if (*currentServiceType == ServiceType::Gaming) result += "���������: ��� \"Valve Corporation\"\n";
			else result += "���������: �� \"���������� ���� �������\"\n";
		}
		result += "��� ������ ����������: " + generateEDRPOU() + "\n" +
			"���� ����������: ��� \"ʳ�����-����\"";
		return result;
	}

};