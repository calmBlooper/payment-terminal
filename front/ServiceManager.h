#pragma once
#include <string>
#include <vector>
#include <QString>
class MobileAccount;
class PrivateAccount;
class PublicAccount;
class EWalletAccount;
class Paycard;
class Service;
class DBManager;
typedef enum {
	Communication = 0,
	Banking,
	Utilities,
	Gaming,
	Charity
} ServiceType;

class CredentialsError {

private:

	const QString _reason;
public:

	CredentialsError(QString reason = "");
	~CredentialsError();
	const QString& getReason() const ;
};

class TransferError {

private:

	const QString _reason;

public:

	TransferError(QString reason = "");
	~TransferError();
	const QString& getReason() const;
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

	DBManager* database;

	std::string generateReceiptNumber();

	std::string generateEDRPOU();
	std::string generateTransactionCode();
	void sendMoney(const double& amount);
	const char* currentTime();
public:

	ServiceManager();

	~ServiceManager();



	const std::string getServiceImageURL(const std::string& serviceName);

	void setCurrentService(const std::string& serviceName);

	const Service& getCurrentService() const;
	const std::string& getCurrentServiceName() const;
	void setCurrentServiceType(const ServiceType& type);

	const ServiceType getCurrentServiceType() const;

	//Use when all the required credentials have been entered and you are ready to work with this account.
	/*
	const Account* getCurrentRecipientAccount() {
		return currentRecipientAccount;
	}
	*/
	//Resets current account, service type and service itself. Useful expecially at the end of session
	void endSession();

	const std::vector <Service> loadServicesByType(const std::string& serviceType);

	//Used with both ewallets and games
	void setRecipientEWalletAccount(const std::string& credentials);

	void setRecipientPublicAccount(const std::string& name);

	void setRecipientPublicAccount(const std::string& name, const std::string& address);

	void setSenderPaycard(const std::string& cardNumber, const __int32& cvv,
		const __int32& expMonth,
		const __int32& expYear);

	bool validateSenderPin(const __int32& pin);

	void setRecipientPaycard(const std::string& cardNumber);

	void setRecipientMobileAccount(const std::string& number);

	double commissionPercentage();

	double minimumAmount();

	double maxCommission();

	void processTransfer(const double& amount);

	double realTransferredAmount(const double& amount);

	std::string doubleToSTDString(const double& number);

	QString getReceipt(const double& amount);

};