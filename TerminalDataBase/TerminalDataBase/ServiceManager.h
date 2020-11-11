#pragma once
#pragma once
#include "DBManager.h"
#include <string>
class ServiceManager {
private:
	Account* currentAccount;
	Service* currentService;
	DBManager database;
	enum class Mode {
		StartMenu,
		ServicesMenu,

	};
public:
	ServiceManager():currentAccount(nullptr),currentService(nullptr) {
		//TODO: upload data to database, or nothing if database is already filled
		return;
	}
	~ServiceManager() {
		currentAccount=nullptr;
		currentService = nullptr;
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
	void deleteCurrentService() {
		currentService = nullptr;
	}
	const std::vector <Service> getServicesByType(const std::string& serviceType) {
		/* Basic indexing of service types, 0-4 accordingly
           enum Type {
                Communication,
                Banking,
                Utilities,
                Gaming,
                Charity
                     };
        */
		if (!serviceType.compare("Мобільний зв'язок")) return database.getServiceRep().getByType(0);
		if (!serviceType.compare("Платіжні системи")) return database.getServiceRep().getByType(1);
		if (!serviceType.compare("Комунальні послуги")) return database.getServiceRep().getByType(2);
		if (!serviceType.compare("Ігри")) return database.getServiceRep().getByType(3);
		if (!serviceType.compare("Благодійність")) return database.getServiceRep().getByType(4);
		throw ("Unknown service type!");
	}
	/// <summary>Finds e-wallet account by the login</summary>
/// <param name="number">Login to look for</param>  
/// <returns>EWalletAccount object with id>0. If id=0, then no such account was found</returns>  
	EWalletAccount getEWalletAccount(const std::string& login) {
		return database.getEWalletRepAcc().getByKey(login);
	};
	/// <summary>Finds mobile account by the number</summary>
/// <param name="number">Number to look for</param>  
/// <returns>MobileAccount object with id>0. If id=0, then no such account was found</returns>  
	MobileAccount getMobileAccount(const std::string& number) {
		return database.getMobileRepAcc().getByKey(number);
	}
	/// <summary>Finds e-wallet account by the login</summary>
/// <param name="number">Login to look for</param>  
/// <returns>EWalletAccount object with id>0. If id=0, then no such account was found</returns>  
	EWalletAccount getEWalletAccount(const std::string& login) {
		return database.getEWalletRepAcc().getByKey(login);
};
	/// <summary>Finds mobile account by the number</summary>
/// <param name="number">Number to look for</param>  
/// <returns>MobileAccount object with id>0. If id=0, then no such account was found</returns>  
	MobileAccount getMobileAccount(const std::string& number) {
		return database.getMobileRepAcc().getByKey(number);
	 }
};