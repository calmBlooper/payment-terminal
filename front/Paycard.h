#pragma once

#include <string>

#include "Identifiable.h"

class Paycard : public Identifiable {
private:
    const __int64 id;
    const __int64 accountId;
    const std::string cardNumber;
    const __int32 cvv;
    const __int32 expMonth;
    const __int32 expYear;
    __int32 pin;

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

    Paycard(const __int64& accountId,
            const std::string& cardNumber,
            const __int32& cvv,
            const __int32& expMonth,
            const __int32& expYear,
            const __int32& pin = 0)
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

    Paycard(const __int64& id,
            const __int64& accountId,
            const std::string& cardNumber,
            const __int32& cvv,
            const __int32& expMonth,
            const __int32& expYear,
            const __int32& pin)
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
    const __int32& getPin() const { return pin; };
    const __int32& getCvv() const { return cvv; };
    const __int32& getExpMonth() const { return expMonth; };
    const __int32& getExpYear() const { return expYear; };

    void setPin(const __int32& newPin)
    {
        pin = (newPin >= 0 && newPin <= 9999) ? newPin : pin;
        return;
    };

};

std::ostream& operator<<(std::ostream& out, const Paycard& p) {
    return out << "id-" << p.getId() << ":" << p.getAccountId() << '|' << p.getCardNumber() << '|' << p.getCvv() << '|' << p.getExpMonth() << '|' << p.getExpYear() << "|" << p.getPin() << "|" << std::endl;
}
