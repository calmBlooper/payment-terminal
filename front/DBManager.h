#pragma once

#include <iostream>
#include <sqlite3.h>
#include <string>

#include "Account.h"
#include "EWalletAccount.h"
#include "MobileAccount.h"
#include "Paycard.h"
#include "PrivateAccount.h"
#include "PublicAccount.h"
#include "Service.h"

#include "PrivateAccountRepository.h"
#include "PublicAccountRepository.h"
#include "MobileAccountRepository.h"
#include "EWalletAccountRepository.h"
#include "ServiceRepository.h"
#include "PaycardRepository.h"

class DBManager {
private:
    PrivateAccountRepository privateRep;
    PublicAccountRepository publicRep;
    MobileAccountRepository mobileRep;
    EWalletAccountRepository ewalletRep;

    ServiceRepository serviceRep;
    PaycardRepository paycardRep;

    const char* dir = "test.db";

public:
    DBManager() {
        DBConnector::InitConnection(dir)->getConnection();
    }
    ~DBManager() {
        DBConnector::InitConnection(dir)->closeConnection();
    }

    PrivateAccountRepository& getPrivateRepAcc() {
        return privateRep;
    }

    PublicAccountRepository& getPublicRepAcc() {
        return publicRep;
    }

    MobileAccountRepository& getMobileRepAcc() {
        return mobileRep;
    }

    EWalletAccountRepository& getEWalletRepAcc() {
        return ewalletRep;
    }

    ServiceRepository& getServiceRep() {
        return serviceRep;
    }

    PaycardRepository& getPaycardRep() {
        return paycardRep;
    }

};
