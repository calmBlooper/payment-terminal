#pragma once

#include <string>

class Paycard {
private:
	const unsigned long id;
	const unsigned long accountId;
	const std::string cardNumber;
	const unsigned short cvv;
	const unsigned short expMonth;
	const unsigned short expYear;
	unsigned short pin;

public:
	Paycard(const unsigned long& id,
		    const unsigned long& accountId,
		    const std::string& cardNumber,
		    const unsigned short& cvv,
		    const unsigned short& expMonth,
		    const unsigned short& expYear,
		    const unsigned short& pin = 0)
		: id(id),
		  accountId(accountId),
		  cardNumber(cardNumber),
		  cvv(cvv),
		  expMonth(expMonth),
		  expYear(expYear),
		  pin(pin)
	{
		return;
	}

	~Paycard() {
		return;
	};

	const unsigned long& getId() const { return id; };
	const unsigned long& getAccountId() const { return accountId; };
	const std::string& getCardNumber() const { return cardNumber; };
	const unsigned short& getPin() const { return pin; };
	const unsigned short& getCvv() const { return cvv; };
	const unsigned short& getExpMonth() const { return expMonth; };
	const unsigned short& getExpYear() const { return expYear; };

	void setPin(const unsigned short& newPin)
	{ 
		pin = (newPin >= 1000 && newPin <= 9999) ? newPin : pin;
		return; 
	};

};