#pragma once

#include <iostream>
#include <string>

#include "Identifiable.h"

class Paycard : public Identifiable {
private:
	const long long id;
	const long long accountId;
	const std::string cardNumber;
	const int cvv;
	const int expMonth;
	const int expYear;
	int pin;

public:
	Paycard()
		: id(0),
		  accountId(0),
		  cardNumber(""),
		  cvv(0),
		  expMonth(0),
		  expYear(0),
		  pin(0)
	{
		return;
	}

	Paycard(const long long& accountId,
		    const std::string& cardNumber,
		    const int& cvv,
		    const int& expMonth,
		    const int& expYear,
		    const int& pin = 0)
        : id(0),
		  accountId(accountId),
		  cardNumber(cardNumber),
		  cvv(cvv),
		  expMonth(expMonth),
		  expYear(expYear),
		  pin(pin)
	{
		return;
	}

	Paycard(const long long& id,
		    const long long& accountId,
		    const std::string& cardNumber,
		    const int& cvv,
		    const int& expMonth,
		    const int& expYear,
		    const int& pin)
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

	virtual const long long& getId() const { return id; };
	const long long& getAccountId() const { return accountId; };
	const std::string& getCardNumber() const { return cardNumber; };
	const int& getPin() const { return pin; };
	const int& getCvv() const { return cvv; };
	const int& getExpMonth() const { return expMonth; };
	const int& getExpYear() const { return expYear; };

	void setPin(const int& newPin)
	{ 
		pin = (newPin >= 0 && newPin <= 9999) ? newPin : pin;
		return; 
	};

};

std::ostream& operator<<(std::ostream&, const Paycard&);