#pragma once

#include <string>

#include "Identifiable.h"

class Paycard : public Identifiable {
private:
	const __int64 id;
	const __int64 accountId;
	const std::string cardNumber;
	const __int8 cvv;
	const __int8 expMonth;
	const __int8 expYear;
	__int8 pin;

public:
	Paycard(const __int64& id,
		    const __int64& accountId,
		    const std::string& cardNumber,
		    const __int8& cvv,
		    const __int8& expMonth,
		    const __int8& expYear,
		    const __int8& pin = 0)
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

	virtual const __int64& getId() const { return id; };
	const __int64& getAccountId() const { return accountId; };
	const std::string& getCardNumber() const { return cardNumber; };
	const __int8& getPin() const { return pin; };
	const __int8& getCvv() const { return cvv; };
	const __int8& getExpMonth() const { return expMonth; };
	const __int8& getExpYear() const { return expYear; };

	void setPin(const __int8& newPin)
	{ 
		pin = (newPin >= 0 && newPin <= 9999) ? newPin : pin;
		return; 
	};

};