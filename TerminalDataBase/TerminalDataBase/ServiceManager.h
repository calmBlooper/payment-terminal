#pragma once
#pragma once
#include "DBManager.h"
#include <string>
typedef enum   {
	Communication = 0,
	Banking,
	Utilities,
	Gaming,
	Charity
} ServiceType;
class ServiceManager {
private:



	MobileAccount* recipientMobileAccount;

	PrivateAccount* recipientPrivateAccount;

	PublicAccount* recipientPublicAccount;

	EWalletAccount* recipientEWalletAccount;

	Service* currentService;

	ServiceType* currentServiceType;

	Paycard* currentSenderPaycard;

	DBManager database;


public:
	class CredentialsError;
	class TransferError;
	ServiceManager();

	~ServiceManager();



	const std::string getServiceImageURL(const std::string& serviceName);

	void setCurrentService(const std::string& serviceName);

	const Service* getCurrentService() const;

	void setCurrentServiceType(const ServiceType& type);

	const ServiceType* getCurrentServiceType() const;

	//Use when all the required credentials have been entered and you are ready to work with this account.
	/*
	const Account* getCurrentRecipientAccount() {
		return currentRecipientAccount;
	}
	*/
	//Resets current account, service type and service itself. Useful expecially at the end of session
	void resetAllCurrentInfo();

	const std::vector <Service> loadServicesByType(const std::string& serviceType);

	//Used with both ewallets and games
	void setRecipientEWalletAccount(const std::string& credentials);

	void setRecipientPublicAccount(const std::string& name, const std::string& address);
	
	void setSenderPaycard(const std::string& cardNumber, const __int32& cvv,
		const __int32& expMonth,
		const __int32& expYear);

	void setRecipientPrivateAccount(const std::string& cardNumber);

	void setRecipientMobileAccount(const std::string& number);

	double commissionPercentage();

	double minimumAmount();

	double maxCommission();

	void sendMoney(const double& amount);

	void processTransfer(const double& amount);

	double realTransferredAmount(const double& amount);

	std::string getReceipt();

};

class ServiceManager::CredentialsError {

private:

	const std::string _reason;

public:

	CredentialsError(std::string reason=""):_reason(reason) {
		return;
	}

	~CredentialsError() {}

	void diagnose()  {
		std::cerr << _reason << std::endl;
	}

};

class ServiceManager::TransferError {

private:
	const std::string _reason;
	const double _minimalAmount;

public:

	TransferError(std::string reason = "",const double minimalAmount=0) :_reason(reason),_minimalAmount(minimalAmount) {
		return;
	}

	~TransferError() {}

	void diagnose() {
		if (_minimalAmount > 0) std::cerr<<_reason << ". Мінімальна сума переказу - " << _minimalAmount << " грн"<<std::endl;
		std::cerr << _reason << std::endl;
	}

};