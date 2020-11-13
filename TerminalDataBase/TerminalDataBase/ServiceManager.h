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
		recipientPrivateAccount = nullptr;
		recipientPublicAccount = nullptr;
		currentService = nullptr;
		currentServiceType = nullptr;
		currentSenderPaycard = nullptr;
	}

	const std::vector <Service> loadServicesByType(const std::string& serviceType) {
		if (!serviceType.compare("Мобільний зв'язок")) setCurrentServiceType(ServiceType::Communication);
		if (!serviceType.compare("Платіжні системи"))  setCurrentServiceType(ServiceType::Banking);
		if (!serviceType.compare("Комунальні послуги")) setCurrentServiceType(ServiceType::Utilities);
		if (!serviceType.compare("Ігри")) setCurrentServiceType(ServiceType::Gaming);
		if (!serviceType.compare("Благодійність")) setCurrentServiceType(ServiceType::Charity);
		return database.getServiceRep().getByType(*currentServiceType);
		throw "Unknown service type!";
	}

	//Used with both ewallets and games
	void setRecipientEWalletAccount(const std::string& credentials) {
		EWalletAccount* result =new EWalletAccount(database.getEWalletRepAcc().getByLogin(credentials));
		if (result->getId() == 0)  result =new EWalletAccount(database.getEWalletRepAcc().getByEmail(credentials)); 
		if (result->getId() == 0) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
		recipientEWalletAccount =new EWalletAccount(*result);
		delete result;
	};

	void setRecipientPublicAccount(const std::string& name, const std::string& address) {
		PublicAccount result = database.getPublicRepAcc().getByKey(name);
		if (result.getId() == 0 || result.getAddress().compare(address)) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
}
	
	void setSenderPaycard(const std::string& cardNumber, const __int32& cvv,
		const __int32& expMonth,
		const __int32& expYear) {
		Paycard result = database.getPaycardRep().getByKey(cardNumber);
		if (result.getId() == 0) throw "Невірно вказаний номер картки";
		if (result.getExpMonth() != expMonth||result.getExpYear()!=expYear||result.getCvv()!=cvv) throw "Будь ласка, перевірте ваші реквізити.Вони некоректні.";
		currentSenderPaycard = new Paycard(result);
	};

	void setRecipientPrivateAccount(const std::string& cardNumber) {
		Paycard result = database.getPaycardRep().getByKey(cardNumber);
		if (result.getId() == 0) throw "Невірно вказаний номер картки";
		recipientPrivateAccount = new PrivateAccount(database.getPrivateRepAcc().getById(result.getAccountId()));
	}
	
	void setRecipientMobileAccount(const std::string& number) {
		MobileAccount result = database.getMobileRepAcc().getByKey(number);
		if (result.getId() == 0) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
		recipientMobileAccount =new MobileAccount(result);
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
		if (recipientPrivateAccount != nullptr) {
			recipientPrivateAccount->replenish(realTransferredAmount(amount), Currency::UAH);
			database.getPrivateRepAcc().update(*recipientPrivateAccount);
			return;
		}
		if (recipientPublicAccount != nullptr) {
			recipientPublicAccount->replenish(realTransferredAmount(amount), Currency::UAH);
			database.getPublicRepAcc().update(*recipientPublicAccount);
			return;
		}
	}
	void processTransfer(const double& amount) {
		if (amount < minimumAmount()) {
			if (currentSenderPaycard == nullptr) throw "Будь ласка, внесіть більшу суму";
			throw "Будь ласка, введіть більшу суму";
		}
		if (currentSenderPaycard == nullptr) {
			sendMoney(amount);
			return;
		}
		PrivateAccount senderAccount = database.getPrivateRepAcc().getById(currentSenderPaycard->getAccountId());
		if (amount>senderAccount.getBalance()) throw "Будь ласка, внесіть більшу суму";
		senderAccount.dismount(amount, Currency::UAH);
		database.getPrivateRepAcc().update(senderAccount);
		sendMoney(amount);
	}

	double realTransferredAmount(const double& amount) {
		double commission = amount / 100.0 * commissionPercentage();
		if (commission > maxCommission()) return maxCommission();
		return commission;
	}

	std::string getReceipt() {
		return "";
	}

};