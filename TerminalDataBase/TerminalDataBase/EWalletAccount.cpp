#include "EWalletAccount.h"

std::ostream& operator<<(std::ostream& out, const EWalletAccount& ewa) {
	return out << "id-" << ewa.getId() << ":" << ewa.getBalance() << ewa.getCurrency() << ',' << ewa.getLogin() << ',' << ewa.getEmail() << std::endl;
}