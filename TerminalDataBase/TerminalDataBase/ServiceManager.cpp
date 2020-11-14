#include "ServiceManager.h"

ServiceManager::ServiceManager() {
	resetAllCurrentInfo();
	//TODO: upload data to database, or nothing if database is already filled
	return;
}

ServiceManager::~ServiceManager() {
	resetAllCurrentInfo();
	return;
}



const std::string ServiceManager::getServiceImageURL(const std::string& serviceName) {
	//TODO: Insert proper path and image format
	return "[base folder path or web-address, containing all the images]/" + serviceName + ".jpg or whatever format";
}

void ServiceManager::setCurrentService(const std::string& serviceName) {
	currentService = new Service(database.getServiceRep().getByKey(serviceName));
}

const Service* ServiceManager::getCurrentService() const {
	return currentService;
}

void ServiceManager::setCurrentServiceType(const ServiceType& type) {
	currentServiceType = new ServiceType(type);
}

const ServiceType* ServiceManager::getCurrentServiceType() const {
	return currentServiceType;
}

//Use when all the required credentials have been entered and you are ready to work with this account.
/*
const Account* getCurrentRecipientAccount() {
	return currentRecipientAccount;
}
*/
//Resets current account, service type and service itself. Useful expecially at the end of session
void ServiceManager::resetAllCurrentInfo() {
	recipientMobileAccount = nullptr;
	recipientEWalletAccount = nullptr;
	recipientPrivateAccount = nullptr;
	recipientPublicAccount = nullptr;
	currentService = nullptr;
	currentServiceType = nullptr;
	currentSenderPaycard = nullptr;
}

const std::vector <Service> ServiceManager::loadServicesByType(const std::string& serviceType) {
	if (!serviceType.compare("Мобільний зв'язок")) setCurrentServiceType(ServiceType::Communication);
	if (!serviceType.compare("Платіжні системи"))  setCurrentServiceType(ServiceType::Banking);
	if (!serviceType.compare("Комунальні послуги")) setCurrentServiceType(ServiceType::Utilities);
	if (!serviceType.compare("Ігри")) setCurrentServiceType(ServiceType::Gaming);
	if (!serviceType.compare("Благодійність")) setCurrentServiceType(ServiceType::Charity);
	return database.getServiceRep().getByType(*currentServiceType);
	throw "Unknown service type!";
}

//Used with both ewallets and games
void ServiceManager::setRecipientEWalletAccount(const std::string& credentials) {
	EWalletAccount* result = new EWalletAccount(database.getEWalletRepAcc().getByLogin(credentials));
	if (result->getId() == 0)  result = new EWalletAccount(database.getEWalletRepAcc().getByEmail(credentials));
	if (result->getId() == 0) throw CredentialsError("Будь ласка, перевірте ваші реквізити. Вони некоректні.");
	recipientEWalletAccount = new EWalletAccount(*result);
	delete result;
};

void ServiceManager::setRecipientPublicAccount(const std::string& name, const std::string& address) {
	PublicAccount result = database.getPublicRepAcc().getByKey(name);
	if (result.getId() == 0 || result.getAddress().compare(address)) throw CredentialsError("Будь ласка, перевірте ваші реквізити. Вони некоректні.");
}

void ServiceManager::setSenderPaycard(const std::string& cardNumber, const __int32& cvv,
	const __int32& expMonth,
	const __int32& expYear) {
	Paycard result = database.getPaycardRep().getByKey(cardNumber);
	if (result.getId() == 0) throw CredentialsError("Невірно вказаний номер картки");
	if (result.getExpMonth() != expMonth || result.getExpYear() != expYear || result.getCvv() != cvv) throw CredentialsError("Будь ласка, перевірте ваші реквізити.Вони некоректні.");
	currentSenderPaycard = new Paycard(result);
};

void ServiceManager::setRecipientPrivateAccount(const std::string& cardNumber) {
	Paycard result = database.getPaycardRep().getByKey(cardNumber);
	if (result.getId() == 0) throw CredentialsError("Невірно вказаний номер картки");
	recipientPrivateAccount = new PrivateAccount(database.getPrivateRepAcc().getById(result.getAccountId()));
}

void ServiceManager::setRecipientMobileAccount(const std::string& number) {
	MobileAccount result = database.getMobileRepAcc().getByKey(number);
	if (result.getId() == 0) throw CredentialsError("Будь ласка, перевірте ваші реквізити. Вони некоректні.");
	recipientMobileAccount = new MobileAccount(result);
}

double ServiceManager::commissionPercentage() {
	return currentService->getCommission();
}

double ServiceManager::minimumAmount() {
	if (*currentServiceType == ServiceType::Communication) return 5;
	return 10;
}

double ServiceManager::maxCommission() {
	if (currentSenderPaycard == nullptr) return 250;
	if (*currentServiceType == ServiceType::Charity) return 50;
	return -1;
}

void ServiceManager::sendMoney(const double& amount) {
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

void ServiceManager::processTransfer(const double& amount) {
	if (amount < minimumAmount()) {
		if (currentSenderPaycard == nullptr) throw TransferError("Будь ласка, внесіть більшу суму", minimumAmount());
		throw TransferError("Будь ласка, введіть більшу суму", minimumAmount());
	}
	if (currentSenderPaycard == nullptr) {
		sendMoney(amount);
		return;
	}
	PrivateAccount senderAccount = database.getPrivateRepAcc().getById(currentSenderPaycard->getAccountId());
	if (amount > senderAccount.getBalance()) throw TransferError("Недостатньо коштів на картці");
	senderAccount.dismount(amount, Currency::UAH);
	database.getPrivateRepAcc().update(senderAccount);
	sendMoney(amount);
}

double ServiceManager::realTransferredAmount(const double& amount) {
	double commission = amount / 100.0 * commissionPercentage();
	if (commission > maxCommission()) return maxCommission();
	return commission;
}

std::string ServiceManager::getReceipt() {
	return "";
}

