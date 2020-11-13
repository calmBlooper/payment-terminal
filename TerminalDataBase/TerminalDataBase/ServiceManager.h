#pragma once
#pragma once
#include "DBManager.h"
#include <string>
class ServiceManager {

private:

	enum ServiceType :unsigned int {
		Communication = 0,
		Banking,
		Utilities,
		Gaming,
		Charity
	};

	Account* currentAccount;

	Service* currentService;

	ServiceType* currentServiceType;

	DBManager database;

	enum class Mode {
		StartMenu,
		ServicesMenu,

	};

public:

	ServiceManager() :currentAccount(nullptr), currentService(nullptr), currentServiceType(nullptr) {
		//TODO: upload data to database, or nothing if database is already filled
		return;
	}

	~ServiceManager() {
		currentAccount = nullptr;
		currentService = nullptr;
		currentServiceType = nullptr;
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

	//Use when all the сщккусе credentials have been entered and you are ready to work with this account.
	void verifyCurrentAccount() {

	}

	const Account* getCurrentAccount() {
		return currentAccount;
	}

	//Resets current account, service type and service itself. Useful expecially at the end of session
	void resetAllCurrent() {
		currentAccount = nullptr;
		currentService = nullptr;
		currentServiceType = nullptr;
	}
	void resetCurrentCard() {

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
	void setEWalletAccount(const std::string& credentials) {
		EWalletAccount* result =new EWalletAccount(database.getEWalletRepAcc().getByLogin(credentials));
		if (result->getId() == 0)  result =new EWalletAccount(database.getEWalletRepAcc().getByEmail(credentials)); 
		if (result->getId() == 0) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
		currentAccount=new EWalletAccount(*result);
		delete result;
	};

	MobileAccount getMobileAccount(const std::string& number) {
		return database.getMobileRepAcc().getByKey(number);
	}
	
	void setEWalletAccount(const std::string& login) {
		result = database.getEWalletRepAcc().getByKey(login);
		if (result.getId() == 0) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
		return result;
	};

	void setMobileAccount(const std::string& number) {
		MobileAccount result = database.getMobileRepAcc().getByKey(number);
		if (result.getId() == 0) throw "Будь ласка, перевірте ваші реквізити. Вони некоректні.";
		currentAccount=new MobileAccount(result);
	}
};