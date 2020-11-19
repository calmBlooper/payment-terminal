#include "PrivateAccount.h"

std::ostream& operator<<(std::ostream& out, const PrivateAccount& pa) {
	return out << "id-" << pa.getId() << ":" << pa.getBalance() << pa.getCurrency() << ',' << pa.getName() << " " << pa.getSurename() << std::endl;
}