#pragma once

#include "Account.h"

class PrivateAccount : public Account {
private:
    const std::string name;
    const std::string surename;

public:
    PrivateAccount(const std::string& name = "", const std::string& surename = ""): Account(), name(name), surename(surename)
    {
        return;
    };

    PrivateAccount(const std::string& currency,
                   const double& initialBalance,
                   const std::string& name,
                   const std::string& surename)
        : Account(0, currency, initialBalance),
          name(name),
          surename(surename)
    {
        return;
    };

    PrivateAccount(const __int64& id,
                   const std::string& currency,
                   const double& initialBalance,
                   const std::string& name,
                   const std::string& surename)
        : Account(id,currency,initialBalance),
        name(name),
        surename(surename)
    {
        return;
    };

    ~PrivateAccount() {
        return;
    };

    const std::string& getName() const { return name; };
    const std::string& getSurename() const { return surename; };

};

std::ostream& operator<<(std::ostream& out, const PrivateAccount& pa) {
    return out << "id-" << pa.getId() << ":" << pa.getBalance() << pa.getCurrency() << ',' << pa.getName() << " " << pa.getSurename() << std::endl;
}
